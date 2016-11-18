//
//  AppDelegate.m
//  RichNotificationExample
//
//  Created by zioolek on 18/11/2016.
//  Copyright © 2016 Ubudu. All rights reserved.
//

#import "AppDelegate.h"
#import <UbuduSDK/UbuduSDK.h>
#import <UserNotifications/UserNotifications.h>

@interface AppDelegate () <UNUserNotificationCenterDelegate>

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    [self setupNotificationCenter];
    [self setupUbuduSDK];
    
    return YES;
}

- (void)setupNotificationCenter
{
    UNUserNotificationCenter.currentNotificationCenter.delegate = self;
    
    [UNUserNotificationCenter.currentNotificationCenter requestAuthorizationWithOptions: UNAuthorizationOptionAlert | UNAuthorizationOptionBadge | UNAuthorizationOptionSound completionHandler:^(BOOL granted, NSError * _Nullable error) {
    }];
}

- (void)setupUbuduSDK
{
    UbuduSDK *sdk = [UbuduSDK sharedInstance];
    
    [sdk setAppNamespace:@"19300bf1225da9d5db5cd28b7a9caddc2b9c6341"];
    [sdk setGeofencesEnabled:NO]; // We don't want to use geofences in this project
    
    NSError *error = nil;
    if (![sdk start:&error]) {
        NSLog(@"Ubudu SDK start error: %@", error);
    }
}

#pragma mark - UNUserNotificationCenterDelegate

- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler
{
    // We want to see a notification even in the foreground so we call completionhandler in any case...
    completionHandler(UNNotificationPresentationOptionAlert);
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)())completionHandler
{
    NSDictionary *payload = [response.notification.request.content.userInfo objectForKey:@"payload"];
    
    NSString *actionIdentifier = response.actionIdentifier;
    
    NSString *urlToOpen = nil;
    
    // In the rule we have specified actions with identifiers:
    // 1 - ubuduActionAboutMeshIdentifier
    // 2 - ubuduActionAboutUbuduIdentifier
    // We also specified custom specific urls in the payload which you can get for keys:
    // 1 - aboutMeshUrl
    // 2 - aboutUbuduUrl
    
    // Determine which action was choosen by user
    if ([actionIdentifier isEqualToString:@"ubuduActionAboutMeshIdentifier"]) {
        urlToOpen = [payload objectForKey:@"aboutMeshUrl"];
    } else if ([actionIdentifier isEqualToString:@"ubuduActionAboutUbuduIdentifier"]) {
        urlToOpen = [payload objectForKey:@"aboutUbuduUrl"];
    }

    // Open the url
    if (urlToOpen != nil) { [[UbuduSDK sharedInstance] openWebPageForUrl:[NSURL URLWithString:urlToOpen]]; }
    
    // Notify ubudu server about opening a notification and eventually execute other actions related to that notification
    // (if specified) like open web page, deep link, wallet...
    [[UbuduSDK sharedInstance] executeNotificationRequestActions:response.notification.request];
    
    // Call a completion handler which notify the system that we've finished handling an action in a custom way...
    completionHandler();
}
@end
