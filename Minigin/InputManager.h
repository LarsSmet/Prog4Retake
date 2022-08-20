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
		Back = 0x0020,
		
		None = 0,
	};



	enum class ActionState
	{
		Up,
		Down,
		Hold
		

	};

	struct ControllerAction //got some help from Laurens Krikilion for the controlleraction part
	{
		ActionState state{};
		ControllerButton button{};
		int controllerIndex = 0;

		auto operator<=>(const ControllerAction&) const = default;

	};

	struct KeyBoardAction 
	{
		ActionState state{};
		SDL_Scancode key{};

		auto operator<=>(const KeyBoardAction&) const = default;

	};



	class InputManager final : public Singleton<InputManager>
	{

		
		
		using ControllerCommandsMap = std::map<ControllerAction, std::shared_ptr<Command>>;
		using KeyBoardCommandsMap = std::map<KeyBoardAction, std::shared_ptr<Command>>;


	public:

		InputManager();
		~InputManager();


		bool ProcessInput();
	
		void HandleInput();
		void BindKey(ControllerAction key, std::shared_ptr<Command> command);
		void BindKey(KeyBoardAction key, std::shared_ptr<Command> command);


		

	private:

		class Impl;
		std::unique_ptr<Impl> m_Impl;

		bool IsUpThisFrame(unsigned int button) const;
		bool IsDownThisFrame(unsigned int button) const;
		bool IsHeld(unsigned int button) const;

		bool IsUpThisFrame(SDL_Keycode key) const;
		bool IsDownThisFrame(SDL_Keycode key) const;
		bool IsHeld(SDL_Keycode key) const;
	};



}