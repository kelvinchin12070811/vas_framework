#pragma once
#include <memory>
#include <functional>

//Prototype of static void defDeleter(SDLComponent* instance)
#define VAS_PROTOTYPE_DEFINE_DEF_DELETER(type) defDeleter(type *instance)

namespace sdl
{
	//Empty component instance
	const class EmptyComponent_t
	{
	public:
		operator std::nullptr_t() const
		{
			return nullptr;
		}
	} emptycomponent = {};

	template <typename SDLComponent, typename SDLWrapedComponent>
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

		bool isEmpty() const
		{
			return this->componentInstance == nullptr;
		}

		operator bool() const
		{
			return !isEmpty();
		}

		bool operator==(std::nullptr_t) const
		{
			return this->componentInstance == nullptr;
		}

		bool operator==(const SDLWrapedComponent& rhs) const
		{
			return this->componentInstance == rhs.componentInstance;
		}

		bool operator!=(std::nullptr_t) const
		{
			return this->componentInstance != nullptr;
		}

		bool operator!=(const SDLWrapedComponent& rhs) const
		{
			return this->componentInstance != rhs.componentInstance;
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

		void destroy()
		{
			this->componentInstance = nullptr;
		}

		std::shared_ptr<SDLComponent> getComponent()
		{
			return this->componentInstance;
		}

		static void notDeleteDeleter(SDLComponent* instance)
		{
			return;
		}
	protected:
		std::shared_ptr<SDLComponent> componentInstance{ nullptr };
	};

	template<typename SDLComponentType, typename SDLComponentRawType>
	SDLComponentType createComponent(SDLComponentRawType* instance, std::function<void(SDLComponentRawType*)> deleter = &SDLComponentType::defDeleter)
	{
		return SDLComponentType(instance, deleter);
	}

	template<typename SDLComponentRawType>
	std::shared_ptr<SDLComponentRawType> createRawComponent(SDLComponentRawType* instance, std::function<void(SDLComponentRawType*)> deleter)
	{
		return std::shared_ptr<SDLComponentRawType>(instance, deleter);
	}
}