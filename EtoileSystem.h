/*
	EtoileSystem.h
 
	Etoile main system process, playing the role of both init process and main 
    server process. It takes care to start, stop and monitor Etoile core 
    processes, possibly restarting them when they die.
 
	Copyright (C) 2006 Quentin Mathe
 
	Author:  Quentin Mathe <qmathe@club-internet.fr>
    Date:  March 2006
 
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.
 
	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.
 
	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#import <Foundation/Foundation.h>

/* Domains are related to CoreObject domains.
   This process is going to be itself registered in CoreObject server under the
   simple 'etoilesystem' entry. Every other core processes related objects will
   have to be registered under this namespace.
   Finally it is logically in charge to start the CoreObject server. */

/** Task/Process Info Dictionary Schema
    
    option                      object type

    LaunchPath                  NSString
    Arguments                   NSString
    UserName (or Identity)      NSString
    OnDemand                    NSNumber/BOOL (0 is NO and 1 is YES)
    Persistent                  NSNumber/BOOL (0 is NO and 1 is YES)
    Hidden                      NSNumber/BOOL (0 is NO and 1 is YES)

    A 'Persistent' process is a task which is restarted on system boot if it
    was already running during the previous session. It is usually bound to 
    tasks running in background.
  */


@interface SCSystem : NSObject
{
    NSMutableDictionary *_processes;

    /* Config file handling related ivars */
    NSTimer *monitoringTimer;
    NSString *configFilePath;
    NSDate *modificationDate;
}

+ (SCSystem *) sharedInstance;

- (id) initWithArguments: (NSArray *)args;

- (BOOL) startProcessWithDomain: (NSString *)domain error: (NSError **)error;
- (BOOL) restartProcessWithDomain: (NSString *)domain error: (NSError **)error;
- (BOOL) stopProcessWithDomain: (NSString *)domain error: (NSError **)error;
- (BOOL) suspendProcessWithDomain: (NSString *)domain error: (NSError **)error;

- (void) run;

- (void) loadConfigList;
- (void) saveConfigList;

- (NSArray *) hiddenProcesses;
- (BOOL) gracefullyTerminateAllProcessesOnOperation: (NSString *)op;

- (oneway void) logOutAndPowerOff: (BOOL) powerOff;

/* SCSystem server daemon set up methods */

+ (id) serverInstance;
+ (BOOL) setUpServerInstance: (id)instance;

@end