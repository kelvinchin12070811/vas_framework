#pragma once
#include <memory>
#include <functional>

//Prototype of static void defDeleter(SDLComponent* instance)
#define VAS_PROTOTYPE_DEFINE_DEF_DELETER(type) defDeleter(type *instance)

namespace vas::sdl
{
	/** @addtogroup sdl_basic
		  @{
	*/
	/** @brief Empty component instance.
		  
		  Represent an empty component instance. The operator used is vas::sdl::emptycomponent. Besides,
		  C++'s operator nullptr also represent as an empty component instance.

		  Just like nullptr The emptycomponent also have a data type (EmptyComponent_t).
	*/
	const class EmptyComponent_t
	{
	public:
		operator std::nullptr_t() const
		{
			return nullptr;
		}
	} emptycomponent = {};

	/** @brief The basic component template of all SDL component.
		  
		  SDLComponentBase is the basic templated interface of all SDL component. This class provided the basic template
		  for the component to work. The empty component can represented as vas::sdl::emptycomponent.

		  A SDL component are able to compare itself with each other to determine if they are same or not. It also be able to
		  reassigend with other instance and the previous one will be deleted when needed. All SDL component use C++
		  Smart Pointer to manage them self therefor resource management are eiser.

		  Besides that, all of the SDL Component are able to convert between raw SDL component type and wrapped type via
		  static_cast. Note that when casting from raw componet, the instance is now a "weak reference" (with
		  notDeleteDeleter of a component). It will not get destroyed when it goes out of scope. To use othe type of deleter,
		  use the overloaded constructor of SDLComponentBase(SDLComponent* component, DeleterType deleter).

		  example: [Component casting example](component_cast_exp.html)
	*/
	template <typename SDLComponent, typename SDLWrapedComponent>
	class SDLComponentBase
	{
	public:
		/** Deleter that use to destroy the component.
			  
			  All of the component have two deleter as bellow
				- defDeleter\n
					Delete the component once it is not used any more, the default deleter of all component.
				- notDeleteDeleter\n
					Do not delete the component, mostly because it is a reference of an instance that returned by raw
					SDL functions which cause auto resource management does not safe.
		*/
		using DeleterType = std::function<void(SDLComponent*)>;
		/** Default constructor that construct a new empty component. */
		SDLComponentBase() {}
		/** Construct a component via an instance of component and a deleter. */
		SDLComponentBase(SDLComponent* component, DeleterType deleter) :
			componentInstance(std::shared_ptr<SDLComponent>(component, deleter))
		{}
		/** Copy constructor. */
		SDLComponentBase(const std::shared_ptr<SDLComponent>& other) :
			componentInstance(other)
		{}
		/** Move constructor. */
		SDLComponentBase(std::shared_ptr<SDLComponent>&& other) :
			componentInstance(std::move(other))
		{}
		~SDLComponentBase() {}

		/** Determine if the component is empty. */
		bool isEmpty() const
		{
			return this->componentInstance == nullptr;
		}
		
		/** Determine if the component is not empty. */
		operator bool() const
		{
			return !isEmpty();
		}

		/** Assign to emptycomponent. */
		bool operator==(std::nullptr_t) const
		{
			return this->componentInstance == nullptr;
		}

		/** Copy assignment. */
		bool operator==(const SDLWrapedComponent& rhs) const
		{
			return this->componentInstance == rhs.componentInstance;
		}

		/** Move assignment. */
		bool operator!=(std::nullptr_t) const
		{
			return this->componentInstance != nullptr;
		}

		/** Check if two component with same type are equal. */
		bool operator!=(const SDLWrapedComponent& rhs) const
		{
			return this->componentInstance != rhs.componentInstance;
		}

		/** Convert to raw SDL component explicitly (using static_cast). */
		explicit operator std::shared_ptr<SDLComponent>()
		{
			return componentInstance;
		}

		/** Convert to raw SDL component explicitly (using static_cast). */
		explicit operator const std::shared_ptr<SDLComponent>() const
		{
			return componentInstance;
		}

		/** Convert to raw SDL component explicitly (using static_cast). */
		explicit operator SDLComponent*()
		{
			return &*componentInstance;
		}

		/** Convert to raw SDL component explicitly (using static_cast). */
		explicit operator const SDLComponent*() const
		{
			return &*componentInstance;
		}

		/** Destroy the component. */
		void destroy()
		{
			this->componentInstance = nullptr;
		}

		/** Get the raw SDL component. */
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
		return SDLComponentType{ instance, deleter };
	}

	template<typename SDLComponentRawType>
	std::shared_ptr<SDLComponentRawType> createRawComponent(SDLComponentRawType* instance, std::function<void(SDLComponentRawType*)> deleter)
	{
		return std::shared_ptr<SDLComponentRawType>(instance, deleter);
	}

	/** @} */
}