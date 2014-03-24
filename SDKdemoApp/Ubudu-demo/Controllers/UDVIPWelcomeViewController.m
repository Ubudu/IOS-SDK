//
//  UDVIPWelcomeViewController.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/5/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import <UbuduIOSSDK/UbuduIOSSDK.h>

#import "UDVIPWelcomeViewController.h"
#import "UDDefinitions.h"

@interface UDVIPWelcomeViewController ()

@property (weak, nonatomic) IBOutlet UIButton *changeButton;
@property (weak, nonatomic) IBOutlet UILabel *clientNameLabel;

@end

@implementation UDVIPWelcomeViewController

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
    self.navigationItem.hidesBackButton = YES;
    self.clientNameLabel.text = kUDDefaultClientName;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - User Name Alert

- (void)promptUserName
{
    UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"Change Name" message:@"What's you name?" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
    alert.alertViewStyle = UIAlertViewStylePlainTextInput;
    [alert show];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    NSString *clientName = [[alertView textFieldAtIndex:0] text];
    self.clientNameLabel.text = clientName;
    [[UbuduIOSSDK sharedInstance] setUser:[[UbuduIOSSDKUser alloc] initWithID:nil withProperties:@{@"ext_id": clientName}]];
    [[UbuduIOSSDK sharedInstance] updateUserInformation];
}

#pragma mark - UI Touch Events

- (IBAction)changeButtonTouched:(id)sender {
    [self promptUserName];
}

@end
