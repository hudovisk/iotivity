/******************************************************************
 *
 * Copyright 2015 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "NSCommon.h"
#include "NSProviderInterface.h"
#include "logger.h"
#include "octypes.h"
#include "pthread.h"
#include "oic_string.h"
#include "oic_malloc.h"

#define TAG "notiProviderExample"

extern char *strdup(const char *s);

bool isExit = false;

int id;

void* OCProcessThread(void * ptr)
{
    (void) ptr;
    while (!isExit)
    {
        if (OCProcess() != OC_STACK_OK)
        {
            OIC_LOG(ERROR, TAG, "OCStack process error");
            return NULL;
        }
    }

    return NULL;
}

void subscribeRequestCallback(NSConsumer *consumer)
{
    OIC_LOG(INFO, TAG, "consumer requested to subscribe");

    printf("NS_APP Consumer Address ID: %s\n", consumer->mAddress);
    printf("NS_APP Consumer Device ID: %s\n", consumer->mDeviceId);

    NSAccept(consumer, true);
}

void syncCallback(NSSync *sync)
{
    OIC_LOG(INFO, TAG, "sync requested");

    printf("NS_APP Sync State: %d\n", sync->mState);
}

int main()
{
    int num;
    pthread_t processThread;

    OIC_LOG(INFO, TAG, "NSStartProvider()");

    if (OCInit(NULL, 0, OC_CLIENT_SERVER) != OC_STACK_OK)
    {
        OIC_LOG(INFO, TAG, "OCStack init error");
        return 0;
    }

    pthread_create(&processThread, NULL, OCProcessThread, NULL);

    while (!isExit)
    {
        char dummy;

        printf("1. NSStartProvider(Accepter: Provider) \n");
        printf("2. NSStartProvider(Accepter: Consumer) \n");
        printf("3. NSSendNotification() \n");
        printf("4. NSRead \n");
        printf("5. NSStopProvider() \n");
        printf("6. NSGetConsumerList \n");
        //printf("7. startPresence \n");
        //printf("8. stopPresence \n");
        printf("0. Exit() \n");

        printf("input : ");

        scanf("%d", &num);
        fflush(stdin);
        scanf("%c", &dummy);
        fflush(stdin);

        switch (num)
        {
            case 1:
                OIC_LOG(INFO, TAG, "NSStartProvider(Accepter: Provider)");
                NSStartProvider(NS_ACCEPTER_PROVIDER, subscribeRequestCallback, syncCallback);
                break;
            case 2:
                OIC_LOG(INFO, TAG, "NSStartProvider(Accepter: Consumer)");
                NSStartProvider(NS_ACCEPTER_CONSUMER, subscribeRequestCallback, syncCallback);
                break;
            case 3:
                OIC_LOG(INFO, TAG, "NSSendNotification()");

                char title[100];
                char body[100];
                char charID[100];

                printf("id : %d\n", ++id);
                printf("title : ");

                gets(title);

                printf("body : ");
                gets(body);

                printf("app - mId : %s \n", charID);
                printf("app - mTitle : %s \n", title);
                printf("app - mContentText : %s \n", body);

                NSMessage * msg = (NSMessage *)OICMalloc(sizeof(NSMessage));

                sprintf(charID, "%d", id);

                msg->mId = strdup(charID);
                msg->mTitle = strdup(title);
                msg->mContentText = OICStrdup(body);
                msg->mSource = NULL;

                NSSendNotification(msg);

                break;

            case 4:
                OIC_LOG(INFO, TAG, "NSRead");
                NSSync * sync = (NSSync*) OICMalloc(sizeof(NSSync));

                sync->mMessageId = OICStrdup("dev_001");
                sync->mState = 1;

                break;

            case 5:
                NSStopProvider();
                break;
            case 6:
                OIC_LOG(INFO, TAG, "NSGetConsumerList");
                break;
            case 7:
                OIC_LOG(INFO, TAG, "NSStartPresence - not working");
                //NSTestStartPresence();
                break;
            case 8:
                OIC_LOG(INFO, TAG, "NSStopPresence- not working");
                //NSTestStopPresence();
                break;
            case 0:
                NSStopProvider();
                isExit = true;
                break;
            default:
                OIC_LOG(INFO, TAG, "Under Construction");
                break;
        }

        printf("\n");
    }

    return 0;
}
