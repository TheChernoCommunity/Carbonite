#pragma once

#include <mono/utils/mono-forward.h>

#include <filesystem>
#include <ostream>

namespace CSharp
{
	enum class EAssemblyLoadStatus : std::uint32_t
	{
		Ok,
		FileNotFound,
		ErrorErrno,
		MissingAssemblyRef,
		ImageInvalid,
		Unknown
	};

	std::ostream& operator<<(std::ostream& stream, EAssemblyLoadStatus status);

	class Assembly;

	class Runtime
	{
	public:
		static Runtime& Get();
		static void     Destroy();

	private:
		static void LoadAssemblyHook(MonoAssembly* monoAssembly, void* userData);

	public:
		void init();
		void deinit();

		Type*       getType(MonoType* type);
		const Type* getType(MonoType* type) const;
		Type*       getType(std::string_view name);
		const Type* getType(std::string_view name) const;
		Type*       getType(std::uint64_t hash);
		const Type* getType(std::uint64_t hash) const;

		Assembly*       getAssembly(std::string_view assemblyName);
		const Assembly* getAssembly(std::string_view assemblyName) const;
		Assembly*       getAssembly(std::uint64_t hash);
		const Assembly* getAssembly(std::uint64_t hash) const;

		Assembly* loadAssembly(const std::filesystem::path& filepath, EAssemblyLoadStatus& status);
		Assembly* loadAssembly(const std::filesystem::path& filepath)
		{
			EAssemblyLoadStatus status;
			return loadAssembly(filepath, status);
		}

		void unloadAssembly(Assembly* assembly);
		void unloadAssembly(const std::filesystem::path& filepath);
		void unloadAssembly(std::uint64_t hash);

	protected:
		Runtime()  = default;
		~Runtime() = default;

	private:
		MonoDomain* m_Domain = nullptr;

		std::unordered_map<std::uint64_t, Assembly*> m_Assemblies;
	};
} // namespace CSharp