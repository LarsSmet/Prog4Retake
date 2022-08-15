#pragma once
#include "windows.h" 
#include "Command.h"
#include <utility>
#include <map>
#include <memory>
#include "Singleton.h"
#include "Command.h"
#include <vector>


namespace dae
{

	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,

		ArrowUp = 0x0001,
		ArrowDown = 0x0002,
		ArrowLeft = 0x0004,
		ArrowRight = 0x0008,
		

		Start = 0x0010,
		Back = 0x0020
		
		
	};



	enum class ActionState
	{
		Up,
		Down,
		Hold
		

	};

	struct ActionKey //got some help from Laurens Krikilion for this.
	{
		ActionState state{};
		ControllerButton button{};

		int controllerIndex = 0;

		auto operator<=>(const ActionKey&) const = default;

	};


	class InputManager final : public Singleton<InputManager>
	{

		
		
		using ControllerCommandsMap = std::map<ActionKey, std::shared_ptr<Command>>;


	public:

		InputManager();
		~InputManager();


		bool ProcessInput();
		bool IsHeld(unsigned int button) const;
		void HandleInput();
		void BindKey(ActionKey key, std::shared_ptr<Command> command);

		

	private:

		class Impl;
		std::unique_ptr<Impl> m_Impl;

		bool IsUpThisFrame(unsigned int button) const;
		bool IsDownThisFrame(unsigned int button) const;
	};



}