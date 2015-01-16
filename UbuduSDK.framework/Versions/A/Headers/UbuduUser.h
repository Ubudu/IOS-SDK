//
//  UbuduUser.h
//  UbuduSDK
//
// Copyright (c) 2011-2014, UBUDU SAS
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//         SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Foundation/Foundation.h>

@interface UbuduUser : NSObject

/* Custom User ID.
 * Typically you use this property to establish a link between the Ubudu users managed by the SDK and the back-office
 * and your users that exist within you information system.
 * When you set this property after the SDK has been started, a request is made to the back-office to update the user information.
 */
@property (nonatomic, copy) NSString *userID;

/* Custom user properties.
 * You can use this property to attach custom properties to your users. These values are sent to the back-office.
 * When you set this property after the SDK has been started, a request is made to the back-office to update the user information.
 *
 * NOTE: The keys "ext_id" and "tags" are reserved by the SDK. If you set them they may be overwritten and never sent to the back-office.
 */
@property (nonatomic, copy) NSDictionary *properties;

/* User tags.
 * Tags are specific properties which can be used to filter and categorize users.
 * In the back-office you can define conditions for your actions that depend on the tags assigned to a user.
 * When you set this property after the SDK has been started, a request is made to the back-office to update the user information.
 */
@property (nonatomic, copy) NSArray *tags;

/* Init the user with the provided ID and properties.
 * Tags will be set to nil.
 */
- (instancetype)initWithID:(NSString *)userID withProperties:(NSDictionary *)properties;

/* Init the user with the provided ID, properties and tags.
 */
- (instancetype)initWithID:(NSString *)userID withProperties:(NSDictionary *)properties tags:(NSArray *)tags;

@end
