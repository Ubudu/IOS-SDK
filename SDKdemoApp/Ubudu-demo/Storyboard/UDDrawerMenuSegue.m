//
//  UDDrawerMenuSegue.m
//  Ubudu-demo
//
//  Created by Jean-Baptiste Quesney on 3/5/14.
//  Copyright (c) 2014 Bistri. All rights reserved.
//

#import "UIViewController+MMDrawerController.h"

#import "UDDrawerMenuSegue.h"

#import "MMDrawerController.h"

@implementation UDDrawerMenuSegue

-(void)perform
{    
    MMDrawerController * drawerController = ((UIViewController*)self.sourceViewController).mm_drawerController;
    [drawerController setCenterViewController:self.destinationViewController withFullCloseAnimation:YES completion:nil];
}

@end
