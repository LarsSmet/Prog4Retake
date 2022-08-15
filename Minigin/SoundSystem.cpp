#include "MiniginPCH.h"
#include "SoundSystem.h"
#include <mutex>

int SDLSoundSystem::s_Head = 0;
int SDLSoundSystem::s_Tail;
const int SDLSoundSystem::s_MaxRequests = 20;
SoundRequest SDLSoundSystem::s_PendingSoundRequests[s_MaxRequests];



SDLSoundSystem::SDLSoundSystem() 
{
	SDL_Init(SDL_INIT_AUDIO);

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);



	s_Head = 0;
	s_Tail = 0;

}

SDLSoundSystem::~SDLSoundSystem()
{
	SDL_Quit();
}

void SDLSoundSystem::PlaySound(SoundRequest request) 
{



	s_PendingSoundRequests[s_Tail].path = request.path;
	s_PendingSoundRequests[s_Tail].volume = request.volume;

	s_Tail = (s_Tail + 1) % s_MaxRequests;


}


Mix_Chunk* SDLSoundSystem::LoadSound(SoundRequest request)  
{
	

	Mix_Chunk* tmpChunk = Mix_LoadWAV(request.path);

	if (tmpChunk != nullptr)
	{
		Mix_VolumeChunk(tmpChunk, int(request.volume));
		return tmpChunk;
	}

	return 0;

}

void SDLSoundSystem::StartSound(Mix_Chunk* soundChunk)//remove this?
{
	Mix_PlayChannel(-1, soundChunk, 0);


}

void SDLSoundSystem::Update() 
{
	//playsound called somewhere in the game
	//adds it to the queue in playsound


	if (s_Head == s_Tail) 
	{
		return;
	}

	std::unique_lock<std::mutex> lock{ m_Mutex };

	Mix_Chunk* tmpChunk = LoadSound(s_PendingSoundRequests[s_Head]);

	StartSound(tmpChunk);



	s_Head = (s_Head + 1) % s_MaxRequests;


	lock.unlock();

}

void NullSoundSystem::PlaySound(SoundRequest request) 
{
	request; 
};

Mix_Chunk* NullSoundSystem::LoadSound(SoundRequest request)
{ 
	request; 
	return nullptr; 
};

void NullSoundSystem::StartSound(Mix_Chunk* soundChunk) 
{ 
	soundChunk; 
};

void NullSoundSystem::Update() 
{

};

NullSoundSystem ServiceLocator::s_DefaultInstance;
SoundSystem* ServiceLocator::s_Instance = &s_DefaultInstance;

void ServiceLocator::RegisterSoundSystem(SoundSystem* soundSystem)
{
	s_Instance = soundSystem == nullptr ? &s_DefaultInstance : soundSystem;
}

SoundSystem& ServiceLocator::GetSoundSystem()
{

	return *s_Instance;


}

void ServiceLocator::DeleteSoundSystem()
{


	delete s_Instance;


	s_Instance = nullptr;



}

void LoggingSoundSystem::PlaySound(SoundRequest request)
{
	s_RealInstance->PlaySound(request);

	std::cout << "Playing from path: " << request.path << " at volume: " << request.volume << '\n';

}

 Mix_Chunk* LoggingSoundSystem::LoadSound(SoundRequest request) 
{
	 std::cout << "Loading sound " << request.path << " at volume: " << request.volume << '\n';
	return s_RealInstance->LoadSound(request);
	
}

 void LoggingSoundSystem::StartSound(Mix_Chunk* soundChunk)
 {
	 s_RealInstance->StartSound(soundChunk);
	 std::cout << "Starting sound " << '\n';
 }

 void LoggingSoundSystem::Update()
 {
	 s_RealInstance->Update();
	 
 }