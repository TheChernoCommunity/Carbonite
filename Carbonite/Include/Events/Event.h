#pragma once

#include <memory>
#include <string>

#include <glfw/glfw3.h>

#include "Utils/Identifiable.h"
#include "Utils/Utils.h"

#include "KeyCodes.h"

// Code derived from https://github.com/TheCherno/Hazel

class Event
{
public:
	enum class Type
	{
		None = 0,
		AppTick,
		AppRender,
		AppUpdate,
		AppClosing,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,
		ControllerButtonPressed,
		ControllerButtonReleased
	};

	enum class Category
	{
		None        = 0,
		Application = bit(0),
		Input       = bit(1),
		Keyboard    = bit(2),
		Mouse       = bit(3),
		MouseButton = bit(4)
	};

	virtual ~Event() = default;

	virtual Type        GetEventType() const     = 0;
	virtual const char* GetName() const          = 0;
	virtual int         GetCategoryFlags() const = 0;
	virtual std::string ToString() const
	{
		return GetName();
	}

	bool IsInCategory(const Category category)
	{
		return GetCategoryFlags() & static_cast<int>(category);
	}

	static void dispatchEvents();
	static void addWindow(GLFWwindow* win);
	static void push(std::shared_ptr<Event> e);
};

#define EVENT_CLASS_TYPE(type)                        \
	static Event::Type GetStaticType()                \
	{                                                 \
		return Event::Type::type;                     \
	}                                                 \
	virtual Event::Type GetEventType() const override \
	{                                                 \
		return GetStaticType();                       \
	}                                                 \
	virtual const char* GetName() const override      \
	{                                                 \
		return #type;                                 \
	}

#define EVENT_CLASS_CATEGORY(category)            \
	virtual int GetCategoryFlags() const override \
	{                                             \
		return static_cast<int>(category);        \
	}


class EventHandler : public Identifiable
{
	friend void Event::dispatchEvents();

public:
	EventHandler();
	~EventHandler();

protected:
	virtual void onEvent(const std::shared_ptr<Event> e) = 0;
};
