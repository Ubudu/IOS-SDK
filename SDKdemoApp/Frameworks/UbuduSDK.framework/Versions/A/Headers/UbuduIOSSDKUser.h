//
//  UbuduIOSSDKUser.h
//  UbuduSDK
//
//  Created by Kevin Bessiere on 28/01/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UbuduIOSSDKUser : NSObject

/* User ID.
 */
@property (nonatomic, strong) NSString * userID;

/* Custom user properties.
 */
@property (nonatomic, strong) NSDictionary * properties;

/* Init the user object with provided ID and properties.
 */
- (id)initWithID:(NSString *)userID withProperties:(NSDictionary *)properties;

@end
