// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_FLUTTERBINARYMESSENGER_H_
#define FLUTTER_FLUTTERBINARYMESSENGER_H_

#import <Foundation/Foundation.h>

#include "FlutterMacros.h"

NS_ASSUME_NONNULL_BEGIN
/**
 A message reply callback.

 Used for submitting a binary reply back to a Flutter message sender. Also used
 in the dual capacity for handling a binary message reply received from Flutter.

 - Parameters:
   - reply: The reply.
 */
typedef void (^FlutterBinaryReply)(NSData* _Nullable reply);

/**
 A strategy for handling incoming binary messages from Flutter and to send
 asynchronous replies back to Flutter.

 - Parameters:
   - message: The message.
   - reply: A callback for submitting a reply to the sender.
 */
typedef void (^FlutterBinaryMessageHandler)(NSData* _Nullable message, FlutterBinaryReply reply);

/**
 A facility for communicating with the Flutter side using asynchronous message
 passing with binary messages.

 - SeeAlso:
   - `FlutterBasicMessageChannel`, which supports communication using structured
 messages.
   - `FlutterMethodChannel`, which supports communication using asynchronous
 method calls.
   - `FlutterEventChannel`, which supports commuication using event streams.
 */
FLUTTER_EXPORT
@protocol FlutterBinaryMessenger<NSObject>
/**
 Sends a binary message to the Flutter side on the specified channel, expecting
 no reply.

 - Parameters:
   - channel: The channel name.
   - message: The message.
 */
- (void)sendOnChannel:(NSString*)channel message:(NSData* _Nullable)message;

/**
 Sends a binary message to the Flutter side on the specified channel, expecting
 an asynchronous reply.

 - Parameters:
   - channel: The channel name.
   - message: The message.
   - callback: A callback for receiving a reply.
 */
- (void)sendOnChannel:(NSString*)channel
              message:(NSData* _Nullable)message
          binaryReply:(FlutterBinaryReply _Nullable)callback;

/**
 Registers a message handler for incoming binary messages from the Flutter side
 on the specified channel.

 Replaces any existing handler. Use a `nil` handler for unregistering the
 existing handler.

 - Parameters:
   - channel: The channel name.
   - handler: The message handler.
 */
- (void)setMessageHandlerOnChannel:(NSString*)channel
              binaryMessageHandler:(FlutterBinaryMessageHandler _Nullable)handler;
@end
NS_ASSUME_NONNULL_END
#endif  // FLUTTER_FLUTTERBINARYMESSENGER_H_
