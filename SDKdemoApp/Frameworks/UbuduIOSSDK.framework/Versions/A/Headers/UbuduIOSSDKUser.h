//
//  UbuduIOSSDKUser.h
//  UbuduIOSSDK
//
//  Created by Kevin Bessiere on 28/01/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UbuduIOSSDKUser : NSObject

@property (nonatomic, strong) NSDictionary * properties;
@property (nonatomic, strong) NSString * userID;

- (id)initWithID:(NSString *)userID withProperties:(NSDictionary *)properties;

@end
