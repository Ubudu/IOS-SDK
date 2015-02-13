//
//  UDScenariosRetailViewController.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/5/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <UbuduSDK/UbuduSDK.h>

#import "UIViewController+MMDrawerController.h"

#import "UDScenariosRetailViewController.h"
#import "UDClickAndCollectViewController.h"

@interface UDScenariosRetailViewController ()

@end

@implementation UDScenariosRetailViewController

#pragma mark - View Lifecycle

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - Status Bar

- (UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Disable menu opening while in a scenario
    [self.mm_drawerController setOpenDrawerGestureModeMask:MMOpenDrawerGestureModeNone];
}

- (IBAction)unwindToScenarios:(UIStoryboardSegue *)segue
{
    // Re-enable the menu opening
    [self.mm_drawerController setOpenDrawerGestureModeMask:MMOpenDrawerGestureModeAll];
}

#pragma mark - UI Touch Events

- (IBAction)resetButtonTouched:(id)sender {
    NSError *error = nil;
    [[UbuduSDK sharedInstance] resetCounters:&error];
}

- (IBAction)leftDrawerButtonTouched:(id)sender
{
    [self.mm_drawerController toggleDrawerSide:MMDrawerSideLeft animated:YES completion:nil];
}

@end
