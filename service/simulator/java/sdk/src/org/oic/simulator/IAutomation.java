/*
 * Copyright 2015 Samsung Electronics All Rights Reserved.
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
 */

/**
 * This file provides an interface for receiving notification when an automation completes.
 */
package org.oic.simulator;

/**
 * Interface for receiving automation complete notifications.
 * 
 * @param resourceURI
 *            URI of the resource on which the automation has occurred.
 * @param automationId
 *            Unique Id of the automation.
 */
public interface IAutomation {
    public void onAutomationComplete(String resourceURI, int automationId);
}
