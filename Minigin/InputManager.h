#pragma once
#include "windows.h"
#include "xinput.h"
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
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,

		ArrowUp = XINPUT_GAMEPAD_DPAD_UP,
		ArrowDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ArrowLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ArrowRight = XINPUT_GAMEPAD_DPAD_RIGHT
		
	};

	class InputManager final : public Singleton<InputManager>
	{

		using ControllerKey = std::pair<unsigned, ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::shared_ptr<Command>>;



	public:

		InputManager();
		~InputManager();


		bool ProcessInput();
		bool IsPressed(unsigned int button) const;
		void HandleInput();
		void BindKey(ControllerKey key, std::shared_ptr<Command> command);

		

	private:

		class Impl;
		std::unique_ptr<Impl> m_Impl;

		bool IsUpThisFrame(unsigned int button) const;
		bool IsDownThisFrame(unsigned int button) const;
	};



}