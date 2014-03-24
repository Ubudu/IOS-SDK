//
//  UDDemoManager.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/11/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import "UDDemoManager.h"
#import "UDDefinitions.h"

@implementation UDDemoManager {
    NSMutableSet *_triggeredNotifications;
}

+ (UDDemoManager *)sharedManager
{
    static UDDemoManager *_sharedManager = nil;
    static dispatch_once_t oncePredicate;
    dispatch_once(&oncePredicate, ^{
        _sharedManager = [[UDDemoManager alloc] init];
    });
    return _sharedManager;
}

- (UDDemoManager *)init
{
    self = [super init];
    if (self != nil) {
        [self _loadTriggeredNotifications];
    }
    return self;
}

- (void)markLocalNotificationAsTrigerred:(UILocalNotification *)localNotification
{
    [_triggeredNotifications addObject:localNotification.alertBody];
    [self _saveTriggeredNotifications];
}

- (BOOL)hasLocalNotificationBeenTriggered:(UILocalNotification *)localNotification
{
    return ([_triggeredNotifications member:localNotification.alertBody] != nil);
}

- (void)clearTriggeredStateForLocalNotification:(UILocalNotification *)localNotification
{
    [_triggeredNotifications removeObject:localNotification.alertBody];
    [self _saveTriggeredNotifications];
}

- (void)clearTriggeredStateForAllLocalNotifications
{
    [_triggeredNotifications removeAllObjects];
    [self _saveTriggeredNotifications];
}

- (void)_loadTriggeredNotifications
{
    NSData *archivedData = [NSData dataWithContentsOfFile:kUDNotificationsFileName];
    if (archivedData != nil) {
        _triggeredNotifications = [NSKeyedUnarchiver unarchiveObjectWithData:archivedData];
    }
    if (_triggeredNotifications == nil) {
        _triggeredNotifications = [[NSMutableSet alloc] init];
    }
}

- (void)_saveTriggeredNotifications
{
    NSData *archivedData = [NSKeyedArchiver archivedDataWithRootObject:_triggeredNotifications];
    [archivedData writeToFile:kUDNotificationsFileName atomically:YES];
}

@end
