#include "PCH.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <queue>
#include <vector>

namespace
{
	static std::queue<std::shared_ptr<Event>> s_queue;
	static std::vector<EventHandler*>         s_handlers;

	void keyCallback([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
	{
		std::shared_ptr<Event> e = nullptr;

		switch (action)
		{
		case GLFW_PRESS:
			e = std::make_shared<KeyPressedEvent>(static_cast<KeyCode>(key), std::uint16_t { 0 });
			break;

		case GLFW_RELEASE:
			e = std::make_shared<KeyReleasedEvent>(static_cast<KeyCode>(key));
			break;
		default:
			return;
			break;
		}

		s_queue.push(e);
	}

	void cursorPositionCallback([[maybe_unused]] GLFWwindow* window, double xpos, double ypos)
	{
		s_queue.push(std::make_shared<MouseMovedEvent>(static_cast<float>(xpos), static_cast<float>(ypos)));
	}

	void mouseButtonCallback([[maybe_unused]] GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
	{
		std::shared_ptr<Event> e = nullptr;

		switch (action)
		{
		case GLFW_PRESS:
			e = std::make_shared<MouseButtonPressedEvent>(static_cast<MouseCode>(button));
			break;

		case GLFW_RELEASE:
			e = std::make_shared<MouseButtonReleasedEvent>(static_cast<MouseCode>(button));
			break;

		default:
			return;
			break;
		}

		s_queue.push(e);
	}

	void scrollCallback([[maybe_unused]] GLFWwindow* window, double xoffset, double yoffset)
	{
		s_queue.push(std::make_shared<MouseScrolledEvent>(static_cast<float>(xoffset), static_cast<float>(yoffset)));
	}

} // namespace

void Event::dispatchEvents()
{
	while (!s_queue.empty())
	{
		for (auto handler : s_handlers)
		{
			(handler->onEvent(s_queue.front()));
		}
		s_queue.pop();
	}
}

void Event::addWindow(GLFWwindow* window)
{
	glfwSetKeyCallback(window, &keyCallback);
	glfwSetCursorPosCallback(window, &cursorPositionCallback);
	glfwSetMouseButtonCallback(window, &mouseButtonCallback);
	glfwSetScrollCallback(window, &scrollCallback);
}

void Event::push(std::shared_ptr<Event> e)
{
	s_queue.push(e);
}

EventHandler::EventHandler()
{
	s_handlers.push_back(this);
}

EventHandler::~EventHandler()
{
	for (auto i = s_handlers.begin(); i != s_handlers.end(); ++i)
	{
		if ((*i)->getID() == this->getID())
		{
			s_handlers.erase(i);
			return;
		}
	}
}
