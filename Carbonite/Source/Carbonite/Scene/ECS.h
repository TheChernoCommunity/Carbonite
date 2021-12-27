#pragma once

#include <entt/entt.hpp>

struct ECS
{
public:
	static ECS& Get();
	static void Destroy();

public:
	auto& getRegistry() { return m_Registry; }
	auto& getRegistry() const { return m_Registry; }

protected:
	ECS();
	~ECS();

private:
	entt::registry m_Registry;
};