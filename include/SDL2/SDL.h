/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute
  it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would
     be appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 * \file SDL.h
 *
 * \brief Main include header for the SDL library.
 *
 * This header includes all of the available SDL subsystem headers.
 * 
 * If you only need a subset of SDL, consider including the relevant headers
 * directly to potentially decrease compile times or avoid unneeded
 * dependencies.
 */

#ifndef SDL_h_
#define SDL_h_

/* Core headers for SDL: main, standard includes, and asserts. */
#include "SDL_main.h"
#include "SDL_stdinc.h"
#include "SDL_assert.h"

/* Atomic operations and concurrency. */
#include "SDL_atomic.h"
#include "SDL_audio.h"

/* Clipboard, CPU info, endianness, and error handling. */
#include "SDL_clipboard.h"
#include "SDL_cpuinfo.h"
#include "SDL_endian.h"
#include "SDL_error.h"

/* Event handling and filesystem utilities. */
#include "SDL_events.h"
#include "SDL_filesystem.h"

/* Game controllers, GUID, haptics, HID, hints, joysticks. */
#include "SDL_gamecontroller.h"
#include "SDL_guid.h"
#include "SDL_haptic.h"
#include "SDL_hidapi.h"
#include "SDL_hints.h"
#include "SDL_joystick.h"

/* Shared object loading, logging, message box, Metal, mutex. */
#include "SDL_loadso.h"
#include "SDL_log.h"
#include "SDL_messagebox.h"
#include "SDL_metal.h"
#include "SDL_mutex.h"

/* Power status, 2D rendering, RWops, sensor, shape, system. */
#include "SDL_power.h"
#include "SDL_render.h"
#include "SDL_rwops.h"
#include "SDL_sensor.h"
#include "SDL_shape.h"
#include "SDL_system.h"

/* Threading, timing, versioning, video, locale, etc. */
#include "SDL_thread.h"
#include "SDL_timer.h"
#include "SDL_version.h"
#include "SDL_video.h"
#include "SDL_locale.h"
#include "SDL_misc.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++. */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name Subsystem Initialization Flags
 *
 * These flags are used with SDL_Init and related functions to selectively
 * initialize or query SDL subsystems. Combine them using bitwise OR.
 */
/*@{*/
#define SDL_INIT_TIMER          0x00000001u    /**< Timer subsystem */
#define SDL_INIT_AUDIO          0x00000010u    /**< Audio subsystem */
#define SDL_INIT_VIDEO          0x00000020u    /**< Video subsystem (implies SDL_INIT_EVENTS) */
#define SDL_INIT_JOYSTICK       0x00000200u    /**< Joystick subsystem (implies SDL_INIT_EVENTS) */
#define SDL_INIT_HAPTIC         0x00001000u    /**< Haptic (force feedback) subsystem */
#define SDL_INIT_GAMECONTROLLER 0x00002000u    /**< Controller subsystem (implies SDL_INIT_JOYSTICK) */
#define SDL_INIT_EVENTS         0x00004000u    /**< Events subsystem */
#define SDL_INIT_SENSOR         0x00008000u    /**< Sensor subsystem */
#define SDL_INIT_NOPARACHUTE    0x00100000u    /**< Deprecated: ignored compatibility flag */

#define SDL_INIT_EVERYTHING ( \
    SDL_INIT_TIMER          | \
    SDL_INIT_AUDIO          | \
    SDL_INIT_VIDEO          | \
    SDL_INIT_EVENTS         | \
    SDL_INIT_JOYSTICK       | \
    SDL_INIT_HAPTIC         | \
    SDL_INIT_GAMECONTROLLER | \
    SDL_INIT_SENSOR         \
)
/*@}*/

/**
 * \brief Initialize the SDL library.
 *
 * \details
 * Calling SDL_Init() starts up the various subsystems specified by \p flags.
 * 
 * Example usage:
 * \code
 *   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
 *       fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
 *       exit(1);
 *   }
 * \endcode
 *
 * \param flags A mask of SDL_INIT_ flags OR'd together.
 *
 * \return 0 on success, or a negative error code on failure. Call SDL_GetError() for more info.
 *
 * \sa SDL_InitSubSystem
 * \sa SDL_Quit
 * \sa SDL_QuitSubSystem
 * \sa SDL_WasInit
 */
extern DECLSPEC int SDLCALL SDL_Init(Uint32 flags);

/**
 * \brief Subsystem-specific initialization, similar to SDL_Init().
 *
 * \details
 * This function allows for more precise control of which subsystems to start.
 * Typically, SDL_Init() is used instead, but SDL_InitSubSystem() can be
 * called multiple times with separate flags to individually activate
 * specific subsystems.
 *
 * \param flags A mask of SDL_INIT_ flags OR'd together.
 *
 * \return 0 on success, or a negative error code on failure.
 *
 * \sa SDL_Init
 * \sa SDL_QuitSubSystem
 */
extern DECLSPEC int SDLCALL SDL_InitSubSystem(Uint32 flags);

/**
 * \brief Shut down specific SDL subsystems.
 *
 * \details
 * This allows for individually stopping certain subsystems (specified by
 * \p flags). The reference count for each subsystem is reduced, and a
 * subsystem will be actually shut down only when the ref count reaches zero.
 *
 * \param flags A mask of SDL_INIT_ flags identifying which subsystems to stop.
 *
 * \sa SDL_InitSubSystem
 * \sa SDL_Quit
 */
extern DECLSPEC void SDLCALL SDL_QuitSubSystem(Uint32 flags);

/**
 * \brief Get the current initialization status.
 *
 * \details
 * You can pass 0 to query all subsystems, or pass a set of flags to see which
 * are currently active.
 *
 * \param flags A bitmask of SDL_INIT_ flags.
 *
 * \return A mask of the active subsystems if \p flags is 0; otherwise, the mask
 *         of subsystems from \p flags that are currently initialized.
 *
 * \sa SDL_Init
 * \sa SDL_InitSubSystem
 */
extern DECLSPEC Uint32 SDLCALL SDL_WasInit(Uint32 flags);

/**
 * \brief Shut down all initialized SDL subsystems.
 *
 * \details
 * Calling SDL_Quit() will properly close all subsystems that have been
 * previously started. Even if SDL_QuitSubSystem() has been called for some
 * parts, it is recommended to call SDL_Quit() to ensure all resources are
 * fully released.
 *
 * Example usage:
 * \code
 *   SDL_Quit();
 * \endcode
 *
 * \sa SDL_Init
 * \sa SDL_QuitSubSystem
 */
extern DECLSPEC void SDLCALL SDL_Quit(void);

/* Close out the C function definitions if compiled as C++. */
#ifdef __cplusplus
}
#endif

#include "close_code.h"

#endif /* SDL_h_ */

/* vi: set ts=4 sw=4 expandtab: */
