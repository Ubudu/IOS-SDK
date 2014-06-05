//
//  UbuduUser.h
//  UbuduSDK
//
//  Created by Kevin Bessiere on 28/01/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UbuduUser : NSObject

/* Custom User ID.
 * Typically you use this property to establish a link between the Ubudu users managed bu the SDK and the back-office
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
- (id)initWithID:(NSString *)userID withProperties:(NSDictionary *)properties;

/* Init the user with the provided ID, properties and tags.
 */
- (id)initWithID:(NSString *)userID withProperties:(NSDictionary *)properties tags:(NSArray *)tags;

@end
