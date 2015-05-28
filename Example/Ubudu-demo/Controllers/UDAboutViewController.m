//
//  UDAboutViewController.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/6/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import "UIViewController+MMDrawerController.h"

#import "UDAboutViewController.h"

@interface UDAboutViewController ()

@end

@implementation UDAboutViewController

#pragma mark - View Lifecycle

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
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

#pragma mark - Navigation

- (IBAction)leftDrawerButtonTouched:(id)sender
{
    [self.mm_drawerController toggleDrawerSide:MMDrawerSideLeft animated:YES completion:nil];
}

@end
