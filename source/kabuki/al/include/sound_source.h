////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2016 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_SOUNDSOURCE_H
#define SFML_SOUNDSOURCE_H

#include <_audio/export.h>
#include <_audio/al_resource.h>
#include <_math/vect3d.h>


namespace sf
{
/** Base class defining a sound's properties.
    @ingroup audio
    @see sf::Sound, sf::SoundStream
    sf::SoundSource is not meant to be used directly, it
    only serves as a common base for all audio objects
    that can live in the audio environment.
   
    It defines several properties for the sound: pitch,
    volume, position, attenuation, etc. All of them can be
    changed at any time with no impact on performances. */
class AUDIO_API SoundSource : AlResource
{
    public:

    /** Enumeration of the sound source states. */
    enum Status
    {
        Stopped, //< Sound is not playing
        Paused,  //< Sound is paused
        Playing  //< Sound is playing
    };

    /** Copy constructor.
        @param copy Instance to copy. */
    SoundSource(const SoundSource& copy);

    /** Destructor. */
    virtual ~SoundSource();
    
    /** Set the pitch of the sound.
        The pitch represents the perceived fundamental frequency
        of a sound; thus you can make a sound more acute or grave
        by changing its pitch. A side effect of changing the pitch
        is to modify the playing speed of the sound as well.
        The default value for the pitch is 1.
        @param pitch New pitch to apply to the sound.
        @see getPitch */
    void setPitch(float pitch);

    /** Set the volume of the sound.
        The volume is a value between 0 (mute) and 100 (full volume).
        The default value for the volume is 100.
        @param volume Volume of the sound.
        @see getVolume */
    void setVolume(float volume);

    /** Set the 3D position of the sound in the audio scene.
        Only sounds with one channel (mono sounds) can be
        spatialized.
        The default position of a sound is (0, 0, 0).
        @param x X coordinate of the position of the sound in the scene.
        @param y Y coordinate of the position of the sound in the scene.
        @param z Z coordinate of the position of the sound in the scene.
        @see getPosition */
    void setPosition(float x, float y, float z);

    /** Set the 3D position of the sound in the audio scene.
        Only sounds with one channel (mono sounds) can be
        spatialized.
        The default position of a sound is (0, 0, 0).
        @param position Position of the sound in the scene.
        @see getPosition */
    void setPosition(const Vector3f& position);

    /** Make the sound's position relative to the listener or absolute.
        Making a sound relative to the listener will ensure that it will always
        be played the same way regardless of the position of the listener.
        This can be useful for non-spatialized sounds, sounds that are
        produced by the listener, or sounds attached to it.
        The default value is false (position is absolute).
        @param relative True to set the position relative, false to set it absolute.
        @see isRelativeToListener */
    void setRelativeToListener(bool relative);

    /** Set the minimum distance of the sound.
        The "minimum distance" of a sound is the maximum
        distance at which it is heard at its maximum volume. Further
        than the minimum distance, it will start to fade out according
        to its attenuation factor. A value of 0 ("inside the head
        of the listener") is an invalid value and is forbidden.
        The default value of the minimum distance is 1.
        @param distance New minimum distance of the sound.
        @see getMinDistance, setAttenuation */
    void setMinDistance(float distance);

    /** Set the attenuation factor of the sound.
        The attenuation is a multiplicative factor which makes
        the sound more or less loud according to its distance
        from the listener. An attenuation of 0 will produce a
        non-attenuated sound, i.e. its volume will always be the same
        whether it is heard from near or from far. On the other hand,
        an attenuation value such as 100 will make the sound fade out
        very quickly as it gets further from the listener.
        The default value of the attenuation is 1.
        @param attenuation New attenuation factor of the sound.
        @see getAttenuation, setMinDistance */
    void setAttenuation(float attenuation);

    /** Get the pitch of the sound.
        @return Pitch of the sound.
        @see setPitch */
    float getPitch() const;

    /** Get the volume of the sound.
        @return Volume of the sound, in the range [0, 100].
        @see setVolume */
    float getVolume() const;

    /** Get the 3D position of the sound in the audio scene.
        @return Position of the sound.
        @see setPosition */
    Vector3f getPosition() const;

    /** Tell whether the sound's position is relative to the
               listener or is absolute.
        @return True if the position is relative, false if it's absolute.
        @see setRelativeToListener */
    bool isRelativeToListener() const;

    /** Get the minimum distance of the sound.
        @return Minimum distance of the sound.
        @see setMinDistance, getAttenuation */
    float getMinDistance() const;

    /** Get the attenuation factor of the sound.
        @return Attenuation factor of the sound.
        @see setAttenuation, getMinDistance */
    float getAttenuation() const;

    /** Overload of assignment operator.
        @param right Instance to assign.
        @return Reference to self. */
    SoundSource& operator =(const SoundSource& right);

protected:

    /** Default constructor.
        This constructor is meant to be called by derived classes only. */
    SoundSource();

    /** Get the current status of the sound (stopped, paused, playing).
        @return Current status of the sound */
    Status getStatus() const;

    unsigned int m_source; //< OpenAL source identifier
};

} // namespace sf


#endif // SFML_SOUNDSOURCE_H