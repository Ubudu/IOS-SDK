//
//  UDMenuViewController.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/5/14.
//  Copyright (c) 2014 Ubudu. All rights reserved.
//

#import "UDMenuViewController.h"

@interface UDMenuViewController ()

@end

@implementation UDMenuViewController

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
    
    UIEdgeInsets insets = UIEdgeInsetsMake(50.0, 0.0, 0.0, 0.0);
    [self.tableView setContentInset:insets];
    [self.tableView setScrollIndicatorInsets:insets];
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

@end
