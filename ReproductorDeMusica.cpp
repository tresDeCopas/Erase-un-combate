#include "MusicPlayer.hpp"
#include "Log.hpp"

MusicPlayer * MusicPlayer::musicPlayer = nullptr;

MusicPlayer * MusicPlayer::getInstance()
{
    if(musicPlayer==nullptr)
        musicPlayer = new MusicPlayer();
    return musicPlayer;
}

void MusicPlayer::load(MusicID identifier, const std::string path)
{
    filenames[identifier] = path;
}

void MusicPlayer::play(MusicID theme)
{
    std::string filename = filenames[theme];

    if(!currentMusic.openFromFile(filename))
        Log::getInstance()->printFileError(filename);

    currentMusic.setLoop(true);
    currentMusic.setVolume(MAX_MUSIC_VOLUME);
    currentMusic.play();
}

void MusicPlayer::stop()
{
    currentMusic.stop();
}

float MusicPlayer::getVolume()
{
    return currentMusic.getVolume();
}

void MusicPlayer::alterVolume(float change)
{
    currentMusic.setVolume(currentMusic.getVolume()+change);
}

void MusicPlayer::loadAllMusic()
{
    load(MusicID::WarningMusic,"music/warning/warningMusic.wav");
}
