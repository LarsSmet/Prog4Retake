#include "MiniginPCH.h"
#include "InputManager.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <iostream>
#pragma comment(lib, "xinput.lib")

namespace dae
{

    using ControllerKey = std::pair<unsigned, dae::ControllerButton>;
    using ControllerCommandsMap = std::map<ControllerKey, std::shared_ptr<Command>>;

    class dae::InputManager::Impl
    {
    public:



        XINPUT_STATE m_PreviousState{};
        XINPUT_STATE m_CurrentState{};


        ControllerCommandsMap m_ConsoleCommands{};


        int m_ButtonsPressedThisFrame{};
        int m_ButtonsReleasedThisFrame{};

    };


    dae::InputManager::InputManager() : m_Impl{ std::make_unique<dae::InputManager::Impl>() }
    {
    }

    dae::InputManager::~InputManager()
    {
    }




    bool dae::InputManager::ProcessInput() 
    {
      
        SDL_Event e;

        while (SDL_PollEvent(&e)) {

   
            switch (e.type) {
           /* case SDL_SCANCODE_W:
                std::cout << "w";
                return true;
                break;*/
         
                
            case SDL_QUIT:
                return false;
                break;
            default:
                break;
            }
        }

        CopyMemory(&m_Impl->m_PreviousState, &m_Impl->m_CurrentState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_Impl->m_CurrentState, sizeof(XINPUT_STATE));
        XInputGetState(0, &m_Impl->m_CurrentState);

        auto buttonChanges = m_Impl->m_CurrentState.Gamepad.wButtons ^ m_Impl->m_PreviousState.Gamepad.wButtons;

        m_Impl->m_ButtonsPressedThisFrame = buttonChanges & m_Impl->m_CurrentState.Gamepad.wButtons;
        m_Impl->m_ButtonsReleasedThisFrame = buttonChanges & (~m_Impl->m_CurrentState.Gamepad.wButtons);
        return true;
    }

    bool dae::InputManager::IsPressed(unsigned int button) const
    {
        return m_Impl->m_CurrentState.Gamepad.wButtons & button;
    }

    void dae::InputManager::HandleInput()
    {

        for (auto command : m_Impl->m_ConsoleCommands) //go over all commands and do the one that matches the pressed button
        {
            if (IsPressed(command.first.first))
            {

                command.second->Execute(); //if pressed this will continue to execute
                if (IsDownThisFrame(command.first.first))
                {
                    //command.second->Execute();
                }

            }
        }

    }

    void dae::InputManager::BindKey(ControllerKey key, std::shared_ptr<Command> command)
    {

        m_Impl->m_ConsoleCommands.insert(std::pair<ControllerKey, std::shared_ptr<Command>>(key, command));
    }

    bool dae::InputManager::IsUpThisFrame(unsigned int button) const
    {
        return m_Impl->m_ButtonsReleasedThisFrame & button;
    }

    bool dae::InputManager::IsDownThisFrame(unsigned int button) const
    {
        return m_Impl->m_ButtonsPressedThisFrame & button;
    }

}