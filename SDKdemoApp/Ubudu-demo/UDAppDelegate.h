//
//  UDAppDelegate.h
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/5/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UbuduIOSSDK/UbuduIOSSDKDelegate.h>

@interface UDAppDelegate : UIResponder <UIApplicationDelegate, UbuduIOSSDKDelegate>

@property (strong, nonatomic) UIWindow *window;

@end
