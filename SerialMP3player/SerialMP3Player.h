#ifndef SERIALMP3PLAYER
#define SERIALMP3PLAYER
#include <Arduino.h>
#include <SoftwareSerial.h>

class SerialMP3Player
{
public:
	// Create the player and uses pin for Rx an TX
	SerialMP3Player(const uint8_t Rx, const uint8_t Tx);
	~SerialMP3Player();
	// needs to be called in the setup of your sketch for initialization
	void 	Setup();
	
	// skip to next song
	void	NextSong();
	// skip to previous song
	void 	PrevSong();
	
	// Start or resume play
	void	Play();
	// play song with index 
	void	Play(const int16_t index);
	// play song with index in folder with index (number 0,1, etc)  
	void	Play(const int8_t FolderIndex, const int8_t SongIndex);
	// play all from folder with index
	void	PlayFolder(const int16_t FolderIndex);
	// pause replay
	void	Pause();
	// stop play
	void	Stop();
		
	// Repeat the current song
	void	PlayRepeat();
	// Stop repeat current song
	void	StopRepeat();
	// enable Shuffle function
	void	PlayShuffle();
	//  Play song index at volume 
	void	PlayAtVolume(const int8_t Index, const uint8_t volume);
	// play several song in a row
	void	PlayGroup(const int size, const int* IndexArray);
	
	// increase volume by 1 step (Max 30)
	void	VolumeUp();
	// decread volume by 1 step (Min 0)
	void	VolumeDown();
	// Set volume at value (0 .. 30)
	void	SetVolume(const uint8_t volume);
	// mute ....
	void	Mute();
	
	// Reset MP3 player hardware
	void 	Reset();
	// Start DAC
	void	StartDAC();
	// Stop DAC
	void	StopDAC();
	// put MP3 hardware to sleep
	void	Sleep();
	// Wake up MP3 hardware 
	void	WakeUp();
	
private:
	// internal function
	void sendCommand(int8_t command);
	void sendCommand(int8_t command, int16_t dat);
	void sendCommand(int8_t command, int8_t dat1,int8_t dat2);
	
	// clips agains min and max volume
	uint8_t	testVolume(uint8_t vol); 
private:
	// not available
	SerialMP3Player(const SerialMP3Player& i);
	SerialMP3Player& operator=(const SerialMP3Player& i);
	
private:
	uint8_t	_Tx;
	uint8_t	_Rx;
	
	const uint8_t _MinVol;
	const uint8_t _MaxVol;
	
	int8_t Send_buf[8];
	SoftwareSerial _Serial;	
	
};


#endif	// SERIALMP3PLAYER