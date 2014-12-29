#include "SerialMP3Player.h" 




/************Command byte**************************/
#define CMD_NEXT_SONG 			0X01
#define CMD_PREV_SONG 			0X02
#define CMD_PLAY_W_INDEX 		0X03
#define CMD_VOLUME_UP 			0X04
#define CMD_VOLUME_DOWN 		0X05
#define CMD_SET_VOLUME 			0X06
#define CMD_SINGLE_CYCLE_PLAY 	0X08
#define CMD_SEL_DEV 			0X09
  #define DEV_TF 				0X02
#define CMD_SLEEP_MODE 			0X0A
#define CMD_WAKE_UP 			0X0B
#define CMD_RESET 				0X0C
#define CMD_PLAY 				0X0D
#define CMD_PAUSE 				0X0E
#define CMD_PLAY_FOLDER_FILE 	0X0F
#define CMD_STOP_PLAY 			0X16
#define CMD_FOLDER_CYCLE 		0X17
#define CMD_SHUFFLE_PLAY 		0X18
#define CMD_SET_SINGLE_CYCLE 	0X19
  #define SINGLE_CYCLE_ON 		0X00
  #define SINGLE_CYCLE_OFF 		0X01
#define CMD_SET_DAC 			0X1A
  #define DAC_ON  				0X00
  #define DAC_OFF 				0X01
#define CMD_GROUP_PLAY	 		0X21
#define CMD_PLAY_W_VOL 			0X22
/**************************************************/

SerialMP3Player::SerialMP3Player(const uint8_t Rx, const uint8_t Tx) :
_MinVol(0),
_MaxVol(30),
_Tx(Tx),
_Rx(Rx),
_Serial(Rx,Tx)
{
}

SerialMP3Player::~SerialMP3Player()
{

}

void
SerialMP3Player::Setup()
{
	_Serial.begin(9600);
	delay(500);
	sendCommand(CMD_SEL_DEV, DEV_TF);
	delay(200);
}

void	SerialMP3Player::NextSong()
{
	sendCommand(CMD_NEXT_SONG);
}

void 	SerialMP3Player::PrevSong()
{
	sendCommand(CMD_PREV_SONG);
}

void	SerialMP3Player::Play()
{
	sendCommand(CMD_PLAY);
}

void	SerialMP3Player::Play(const int16_t index)
{
	sendCommand(CMD_PLAY_W_INDEX,index);
}

void	SerialMP3Player::Play(const int8_t FolderIndex, const int8_t SongIndex)
{
	sendCommand(CMD_PLAY_FOLDER_FILE,(uint8_t) FolderIndex,(uint8_t) SongIndex);
}

void	SerialMP3Player::PlayFolder(const int16_t FolderIndex)
{
	sendCommand(CMD_FOLDER_CYCLE,FolderIndex);
}

void	SerialMP3Player::Pause()
{
	sendCommand(CMD_PAUSE);
}

void	SerialMP3Player::Stop()
{
	sendCommand(CMD_STOP_PLAY);
}
	
void	SerialMP3Player::PlayRepeat()
{
	sendCommand(CMD_SET_SINGLE_CYCLE,SINGLE_CYCLE_ON);
}

void	SerialMP3Player::StopRepeat()
{
	sendCommand(CMD_SET_SINGLE_CYCLE,SINGLE_CYCLE_OFF);	
}

void	SerialMP3Player::PlayShuffle()
{
	sendCommand(CMD_SHUFFLE_PLAY);
}

void	SerialMP3Player::PlayAtVolume(const int8_t Index, const uint8_t volume)
{
	sendCommand(CMD_PLAY_W_VOL,testVolume(volume));
}

void	SerialMP3Player::PlayGroup(const int size, const int* IndexArray)
{
	uint8_t bufferSize = size+6;
	uint8_t* buffer=new uint8_t[(bufferSize)];
	
	buffer[0] = 0x7e; //
	buffer[1] = 0xff; //
	buffer[2] = 0x06; //
	buffer[3] = CMD_GROUP_PLAY; //
	buffer[4] = 0x00;//
	buffer[size+5] = 0xEF;
	
	for(uint8_t i=0;i<size;i++)
	{
		buffer[i+5] = IndexArray[i];
	}
	for(uint8_t i=0; i<bufferSize; i++)//
	{
	    _Serial.write(buffer[i]) ;
	}
	
	delete [] buffer;
}


void	SerialMP3Player::VolumeUp()
{
	sendCommand(CMD_VOLUME_UP);
}

void	SerialMP3Player::Sleep()
{
	sendCommand(CMD_SLEEP_MODE);
}

void	SerialMP3Player::WakeUp()
{
	sendCommand(CMD_WAKE_UP);
}

void	SerialMP3Player::VolumeDown()
{
	sendCommand(CMD_VOLUME_DOWN);
}

void	SerialMP3Player::SetVolume(const uint8_t volume)
{
	sendCommand(CMD_SET_VOLUME,testVolume(volume));
}
void	SerialMP3Player::Mute()
{
	sendCommand(CMD_SET_VOLUME,0);
}

void 	SerialMP3Player::Reset()
{
	sendCommand(CMD_RESET);
}
void	SerialMP3Player::StartDAC()
{
	sendCommand(CMD_SET_DAC,DAC_ON);
}

void	SerialMP3Player::StopDAC()
{
	sendCommand(CMD_SET_DAC,DAC_OFF);
}

uint8_t	SerialMP3Player::testVolume(uint8_t vol)
{
	if(vol>30) vol = 30;
	if(vol<0)  vol = 0;
	return vol;
}

void SerialMP3Player::sendCommand(int8_t command)
{
  delay(20);
  Send_buf[0] = 0x7e; //
  Send_buf[1] = 0xff; //
  Send_buf[2] = 0x06; //
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//
  Send_buf[5] = 0;
  Send_buf[6] = 0;
  Send_buf[7] = 0xef; //
  for(uint8_t i=0; i<8; i++)//
  {
   _Serial.write(Send_buf[i]) ;
  }
}

void SerialMP3Player::sendCommand(int8_t command, int8_t dat1,int8_t dat2)
{
  delay(20);
  Send_buf[0] = 0x7e; //
  Send_buf[1] = 0xff; //
  Send_buf[2] = 0x06; //
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//
  Send_buf[5] = (int8_t)(dat1);//datah
  Send_buf[6] = (int8_t)(dat2); //datal
  Send_buf[7] = 0xef; //
  for(uint8_t i=0; i<8; i++)//
  {
    _Serial.write(Send_buf[i]) ;
  }
}

void SerialMP3Player::sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e; //
  Send_buf[1] = 0xff; //
  Send_buf[2] = 0x06; //
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //
  for(uint8_t i=0; i<8; i++)//
  {
    _Serial.write(Send_buf[i]) ;
  }
}