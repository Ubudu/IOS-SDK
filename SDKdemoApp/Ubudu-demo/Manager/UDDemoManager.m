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
    NSMutableDictionary *_triggeredNotifications;
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

- (void)markLocalNotificationAsTrigerred:(NSString *)localNotification
{
    [_triggeredNotifications setObject:[NSDate date] forKey:localNotification];
    [self _saveTriggeredNotifications];
}

- (BOOL)hasLocalNotificationBeenTriggered:(NSString *)localNotification
{
    return ([_triggeredNotifications objectForKey:localNotification] != nil);
}

- (NSDate *)lastNotificationTriggerDate:(NSString *)localNotification
{
    return [_triggeredNotifications objectForKey:localNotification];
}

- (void)clearTriggeredStateForLocalNotification:(NSString *)localNotification
{
    [_triggeredNotifications removeObjectForKey:localNotification];
    [self _saveTriggeredNotifications];
}

- (void)clearTriggeredStateForAllLocalNotifications
{
    [_triggeredNotifications removeAllObjects];
    [self _saveTriggeredNotifications];
}

- (void)_loadTriggeredNotifications
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *fileName = [NSString stringWithFormat:@"%@/%@", documentsDirectory, kUDNotificationsFileName];
    
    NSData *archivedData = [NSData dataWithContentsOfFile:fileName];
    if (archivedData != nil) {
        _triggeredNotifications = [NSKeyedUnarchiver unarchiveObjectWithData:archivedData];
    }
    if (_triggeredNotifications == nil) {
        _triggeredNotifications = [[NSMutableDictionary alloc] init];
    }
}

- (void)_saveTriggeredNotifications
{
    NSData *archivedData = [NSKeyedArchiver archivedDataWithRootObject:_triggeredNotifications];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *fileName = [NSString stringWithFormat:@"%@/%@", documentsDirectory, kUDNotificationsFileName];
    
    NSError *error = nil;
    [archivedData writeToFile:fileName options:NSDataWritingAtomic error:&error];
}

@end
