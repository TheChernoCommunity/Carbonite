#include "PCH.h"

#include "Assembly.h"
#include "Runtime.h"
#include "Utils/FileIO.h"

#include <mono/jit/jit.h>
#include <mono/jit/mono-private-unstable.h>
#include <mono/metadata/assembly.h>

#include <string>
#include <xhash>

namespace CSharp
{
	static std::string GetAssemblyName(const std::filesystem::path& filepath)
	{
		return filepath.filename().replace_extension().string();
	}

	std::ostream& operator<<(std::ostream& stream, EAssemblyLoadStatus status)
	{
		switch (status)
		{
		case EAssemblyLoadStatus::Ok: return stream << "Ok";
		case EAssemblyLoadStatus::FileNotFound: return stream << "File Not Found";
		case EAssemblyLoadStatus::ErrorErrno: return stream << mono_image_strerror(MONO_IMAGE_ERROR_ERRNO);
		case EAssemblyLoadStatus::MissingAssemblyRef: return stream << mono_image_strerror(MONO_IMAGE_MISSING_ASSEMBLYREF);
		case EAssemblyLoadStatus::ImageInvalid: return stream << mono_image_strerror(MONO_IMAGE_IMAGE_INVALID);
		case EAssemblyLoadStatus::Unknown: return stream << "Uknown";
		default: return stream << "Uknown";
		}
	}

	Runtime& Runtime::Get()
	{
		static Runtime* s_Instance = new Runtime();
		return *s_Instance;
	}

	void Runtime::Destroy()
	{
		delete &Get();
	}

	void Runtime::LoadAssemblyHook(MonoAssembly* monoAssembly, [[maybe_unused]] void* userData)
	{
		auto& runtime = Get();

		std::uint64_t hash = std::hash<std::string_view>()(mono_assembly_name_get_name(mono_assembly_get_name(monoAssembly)));
		if (runtime.m_Assemblies.find(hash) != runtime.m_Assemblies.end())
			return;

		Assembly* assembly = new Assembly(hash, monoAssembly, mono_assembly_get_image(monoAssembly));
		runtime.m_Assemblies.insert({ assembly->m_Hash, assembly });
	}

	void Runtime::init()
	{
		std::vector<std::string> tpaList;
		for (auto& entry : std::filesystem::recursive_directory_iterator(FileIO::getExecutableDir() / ".NET"))
		{
			auto& path = entry.path();
			if (path.extension() != ".dll")
				continue;

			tpaList.emplace_back(path.string());
		}
		tpaList.emplace_back((FileIO::getExecutableDir() / "System.IO.Compression.Native.dll").string());
		tpaList.emplace_back((FileIO::getExecutableDir() / "System.Private.CoreLib.dll").string());

		std::string tpaListStr;
		for (auto& tpa : tpaList)
		{
			tpaListStr += tpa;
			if constexpr (Core::s_IsSystemWindows)
				tpaListStr += ';';
			else
				tpaListStr += ':';
		}

		const char*  propertyKeys[]   = { "TRUSTED_PLATFORM_ASSEMBLIES" };
		const char*  propertyValues[] = { tpaListStr.c_str() };
		std::int32_t propertyCount    = sizeof(propertyKeys) / sizeof(propertyKeys[0]);

		std::int32_t monoVMStatus = monovm_initialize(propertyCount, propertyKeys, propertyValues);
		if (monoVMStatus)
			throw std::runtime_error("Mono VM failed to initialize");

		m_Domain = mono_jit_init("Carbonite");

		mono_install_assembly_load_hook(&Runtime::LoadAssemblyHook, nullptr);
	}

	void Runtime::deinit()
	{
		for (auto& assembly : m_Assemblies)
			delete assembly.second;
		m_Assemblies.clear();

		if (m_Domain)
		{
			mono_jit_cleanup(m_Domain);
			m_Domain = nullptr;
		}
	}

	Type* Runtime::getType(MonoType* type)
	{
		return getType(mono_type_get_name_full(type, MONO_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED));
	}

	const Type* Runtime::getType(MonoType* type) const
	{
		return getType(mono_type_get_name_full(type, MONO_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED));
	}

	Type* Runtime::getType(std::string_view name)
	{
		return getType(std::hash<std::string_view>()(name));
	}

	const Type* Runtime::getType(std::string_view name) const
	{
		return getType(std::hash<std::string_view>()(name));
	}

	Type* Runtime::getType([[maybe_unused]] std::uint64_t hash)
	{
		// TODO(MarcasRealAccount): Implement Type!
		return nullptr;
	}

	const Type* Runtime::getType([[maybe_unused]] std::uint64_t hash) const
	{
		return nullptr;
	}

	Assembly* Runtime::getAssembly(std::string_view assemblyName)
	{
		return getAssembly(std::hash<std::string_view>()(assemblyName));
	}

	const Assembly* Runtime::getAssembly(std::string_view assemblyName) const
	{
		return getAssembly(std::hash<std::string_view>()(assemblyName));
	}

	Assembly* Runtime::getAssembly(std::uint64_t hash)
	{
		auto itr = m_Assemblies.find(hash);
		return itr != m_Assemblies.end() ? itr->second : nullptr;
	}

	const Assembly* Runtime::getAssembly(std::uint64_t hash) const
	{
		auto itr = m_Assemblies.find(hash);
		return itr != m_Assemblies.end() ? itr->second : nullptr;
	}

	Assembly* Runtime::loadAssembly(const std::filesystem::path& filepath, EAssemblyLoadStatus& status)
	{
		status = EAssemblyLoadStatus::Unknown;

		std::filesystem::path realFilepath     = std::filesystem::canonical(filepath);
		std::string           realFilepathStr  = realFilepath.string();
		std::uint64_t         realFilepathHash = std::hash<std::string_view>()(GetAssemblyName(realFilepath));

		Assembly* assembly = getAssembly(realFilepathHash);
		if (assembly) return assembly;

		if (!std::filesystem::exists(realFilepath))
		{
			status = EAssemblyLoadStatus::FileNotFound;
			return nullptr;
		}

		MonoImageOpenStatus            monoStatus;
		[[maybe_unused]] MonoAssembly* monoAssembly = mono_assembly_open_full(realFilepathStr.c_str(), &monoStatus, false);
		if (monoStatus != MONO_IMAGE_OK)
		{
			switch (monoStatus)
			{
			case MONO_IMAGE_ERROR_ERRNO:
				status = EAssemblyLoadStatus::ErrorErrno;
				break;
			case MONO_IMAGE_MISSING_ASSEMBLYREF:
				status = EAssemblyLoadStatus::MissingAssemblyRef;
				break;
			case MONO_IMAGE_IMAGE_INVALID:
				status = EAssemblyLoadStatus::ImageInvalid;
				break;
			}
			return nullptr;
		}

		status = EAssemblyLoadStatus::Ok;
		return getAssembly(realFilepathHash);
	}

	void Runtime::unloadAssembly(Assembly* assembly)
	{
		if (assembly)
			unloadAssembly(assembly->m_Hash);
	}

	void Runtime::unloadAssembly(const std::filesystem::path& filepath)
	{
		unloadAssembly(std::hash<std::string_view>()(filepath.string()));
	}

	void Runtime::unloadAssembly(std::uint64_t hash)
	{
		auto itr = m_Assemblies.find(hash);
		if (itr != m_Assemblies.end())
		{
			delete itr->second;
			m_Assemblies.erase(itr);
		}
	}
} // namespace CSharp