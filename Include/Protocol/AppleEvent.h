/** @file
  Copyright (C) 2005 - 2017, Apple Inc.  All rights reserved.
  Portions Copyright (C) 2014 - 2017, CupertinoNet.  All rights reserved.<BR>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
**/

#ifndef APPLE_EVENT_H_
#define APPLE_EVENT_H_

// Related definitions

// Apple Event Type

#define APPLE_EVENT_TYPE_NONE                0
#define APPLE_EVENT_TYPE_MOUSE_MOVED         BIT0
#define APPLE_EVENT_TYPE_MOUSE_DOWN          BIT1
#define APPLE_EVENT_TYPE_MOUSE_UP            BIT2
#define APPLE_EVENT_TYPE_MOUSE_CLICK         BIT3
#define APPLE_EVENT_TYPE_MOUSE_DOUBLE_CLICK  BIT4
#define APPLE_EVENT_TYPE_LEFT_BUTTON         BIT5
#define APPLE_EVENT_TYPE_RIGHT_BUTTON        BIT6
#define APPLE_EVENT_TYPE_RESERVED_BUTTON     BIT7
#define APPLE_EVENT_TYPE_KEY_DOWN            BIT8
#define APPLE_EVENT_TYPE_KEY_UP              BIT9
#define APPLE_EVENT_TYPE_MODIFIER_DOWN       BIT10
#define APPLE_EVENT_TYPE_MODIFIER_UP         BIT11

#define APPLE_CLICK_MOUSE_EVENTS   \
  (APPLE_EVENT_TYPE_MOUSE_DOWN     \
 | APPLE_EVENT_TYPE_MOUSE_UP       \
 | APPLE_EVENT_TYPE_MOUSE_CLICK    \
 | APPLE_EVENT_TYPE_LEFT_BUTTON    \
 | APPLE_EVENT_TYPE_RIGHT_BUTTON)

#define APPLE_ALL_MOUSE_EVENTS     0x00FF
#define APPLE_ALL_KEYBOARD_EVENTS  0xFF00

// APPLE_EVENT_TYPE
typedef UINT32 APPLE_EVENT_TYPE;

// APPLE_POINTER_EVENT_TYPE
typedef UINTN APPLE_POINTER_EVENT_TYPE;

// APPLE_KEY_EVENT_DATA
typedef PACKED struct {
  UINT16 NumberOfKeyPairs;        ///<
  PACKED struct {
    EFI_INPUT_KEY  InputKey;      ///<
    APPLE_KEY_CODE AppleKeyCode;  ///<
  }      KeyPair;                 ///<
  UINT16 Unknown;                 ///<
} APPLE_KEY_EVENT_DATA;

typedef union {
  APPLE_KEY_EVENT_DATA     *KeyData;          ///< 
  APPLE_POINTER_EVENT_TYPE PointerEventType;  ///< 
  UINTN                    Raw;               ///< 
} APPLE_EVENT_DATA;

// DIMENSION
typedef struct {
  INT32 Horizontal;  ///< 
  INT32 Vertical;    ///< 
} DIMENSION;

// APPLE_EVENT_INFORMATION
typedef struct {
  struct {
    UINT16 Year;    ///< 
    UINT8  Month;   ///< 
    UINT8  Day;     ///< 
    UINT8  Hour;    ///< 
    UINT8  Minute;  ///< 
    UINT8  Second;  ///< 
    UINT8  Pad1;    ///< 
  }                  CreationTime;     ///< 
  APPLE_EVENT_TYPE   EventType;        ///< 
  APPLE_EVENT_DATA   EventData;        ///< 
  APPLE_MODIFIER_MAP Modifiers;        ///< 
  DIMENSION          PointerPosition;  ///< 
} APPLE_EVENT_INFORMATION;

// APPLE_EVENT_NOTIFY_FUNCTION
typedef
VOID
(EFIAPI *APPLE_EVENT_NOTIFY_FUNCTION)(
  IN APPLE_EVENT_INFORMATION  *Information,
  IN VOID                     *NotifyContext
  );

typedef VOID *APPLE_EVENT_HANDLE;

// Protocol declaration

// APPLE_EVENT_PROTOCOL_GUID
#define APPLE_EVENT_PROTOCOL_GUID                         \
  { 0x33BE0EF1, 0x89C9, 0x4A6D,                           \
    { 0xBB, 0x9F, 0x69, 0xDC, 0x8D, 0xD5, 0x16, 0xB9 } }

// EVENT_REGISTER_HANDLER
typedef
EFI_STATUS
(EFIAPI *EVENT_REGISTER_HANDLER)(
  IN  APPLE_EVENT_TYPE             Type,
  IN  APPLE_EVENT_NOTIFY_FUNCTION  NotifyFunction,
  OUT APPLE_EVENT_HANDLE           *Handle,
  IN  VOID                         *NotifyContext
  );

// EVENT_UNREGISTER_HANDLER
typedef
EFI_STATUS
(EFIAPI *EVENT_UNREGISTER_HANDLER)(
  IN APPLE_EVENT_HANDLE  EventHandle
  );

// EVENT_SET_CURSOR_POSITION
typedef
EFI_STATUS
(EFIAPI *EVENT_SET_CURSOR_POSITION)(
  IN DIMENSION  *Position
  );

// EVENT_SET_EVENT_NAME
typedef
EFI_STATUS
(EFIAPI *EVENT_SET_EVENT_NAME)(
  IN OUT APPLE_EVENT_HANDLE  Handle,
  IN     CHAR8               *Name
  );

// EVENT_IS_CAPS_LOCK_ON
/** Retrieves the state of the CapsLock key.

  @param[in, out] CLockOn  This parameter indicates the state of the CapsLock
                           key.

  @retval EFI_SUCCESS            The CapsLock state was successfully returned
                                 in CLockOn.
  @retval EFI_INVALID_PARAMETER  CLockOn is NULL.
**/
typedef
EFI_STATUS
(EFIAPI *EVENT_IS_CAPS_LOCK_ON)(
  IN OUT BOOLEAN  *CLockOn
  );

// APPLE_EVENT_PROTOCOL
typedef struct {
  UINT32                    Revision;           ///< 
  EVENT_REGISTER_HANDLER    RegisterHandler;    ///< 
  EVENT_UNREGISTER_HANDLER  UnregisterHandler;  ///< 
  EVENT_SET_CURSOR_POSITION SetCursorPosition;  ///< 
  EVENT_SET_EVENT_NAME      SetEventName;       ///< 
  EVENT_IS_CAPS_LOCK_ON     IsCapsLockOn;       ///< 
} APPLE_EVENT_PROTOCOL;

// gAppleEventProtocolGuid
extern EFI_GUID gAppleEventProtocolGuid;

#endif // APPLE_EVENT_H_
