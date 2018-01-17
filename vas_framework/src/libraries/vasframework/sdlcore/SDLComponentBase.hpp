#pragma once
#include <memory>
#include <functional>

namespace sdl
{
	template <typename SDLComponent>
	class SDLComponentBase
	{
	public:
		using DeleterType = std::function<void(SDLComponent*)>;
		SDLComponentBase() {}
		SDLComponentBase(SDLComponent* component, DeleterType deleter) :
			componentInstance(std::shared_ptr<SDLComponent>(component, deleter))
		{}
		SDLComponentBase(const std::shared_ptr<SDLComponent>& other) :
			componentInstance(other)
		{}
		SDLComponentBase(std::shared_ptr<SDLComponent>&& other) :
			componentInstance(std::move(other))
		{}
		~SDLComponentBase() {}

		void destroy() const
		{
			this->componentInstance == nullptr;
		}

		bool isEmpty()
		{
			return this->componentInstance == nullptr;
		}

		operator bool() const
		{
			return !isEmpty();
		}

		bool operator==(std::nullptr_t ptr) const
		{
			return this->componentInstance == ptr;
		}

		bool operator!=(std::nullptr_t ptr) const
		{
			return this->componentInstance != ptr;
		}

		explicit operator std::shared_ptr<SDLComponent>()
		{
			return componentInstance;
		}

		explicit operator const std::shared_ptr<SDLComponent>() const
		{
			return componentInstance;
		}

		explicit operator SDLComponent*()
		{
			return &*componentInstance;
		}

		explicit operator const SDLComponent*() const
		{
			return &*componentInstance;
		}

		std::shared_ptr<SDLComponent> getComponent()
		{
			return this->componentInstance;
		}
	protected:
		std::shared_ptr<SDLComponent> componentInstance = nullptr;
	};

	template<typename SDLComponentType, typename SDLComponentRawType>
	SDLComponentType createComponent(SDLComponentRawType* instance, std::function<void(SDLComponentRawType*)> deleter = &SDLComponentType::defDeleter)
	{
		return SDLComponentType(instance, deleter);
	}
}