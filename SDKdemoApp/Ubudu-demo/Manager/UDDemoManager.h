//
//  UDDemoManager.h
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/11/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UDDemoManager : NSObject

+ (UDDemoManager *)sharedManager;

#pragma mark - Notifications management

- (void)markLocalNotificationAsTrigerred:(UILocalNotification *)localNotification;
- (BOOL)hasLocalNotificationBeenTriggered:(UILocalNotification *)localNotification;
- (void)clearTriggeredStateForLocalNotification:(UILocalNotification *)localNotification;
- (void)clearTriggeredStateForAllLocalNotifications;

@end
