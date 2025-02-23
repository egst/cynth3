/*
 * Copyright (C) 2017 Devin Rousso <webkit@devinrousso.com>. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

WI.WebSocketResourceTreeElement = class WebSocketResourceTreeElement extends WI.ResourceTreeElement
{
    // Overrides from TreeElement

    onattach()
    {
        super.onattach();

        this._updateConnectionStatus();

        this.resource.addEventListener(WI.WebSocketResource.Event.ReadyStateChanged, this._updateConnectionStatus, this);
    }

    ondetach()
    {
        super.ondetach();

        this.resource.removeEventListener(WI.WebSocketResource.Event.ReadyStateChanged, this._updateConnectionStatus, this);
    }

    populateContextMenu(contextMenu, event)
    {
        contextMenu.appendItem(WI.UIString("Log WebSocket"), () => {
            WI.RemoteObject.resolveWebSocket(this._resource, WI.RuntimeManager.ConsoleObjectGroup, (remoteObject) => {
                if (!remoteObject)
                    return;

                const text = WI.UIString("Selected WebSocket");
                const addSpecialUserLogClass = true;
                WI.consoleLogViewController.appendImmediateExecutionWithResult(text, remoteObject, addSpecialUserLogClass);
            });
        });

        contextMenu.appendSeparator();

        super.populateContextMenu(contextMenu, event);
    }

    // Private

    _updateConnectionStatus()
    {
        switch (this.resource.readyState) {
        case WI.WebSocketResource.ReadyState.Closed:
            this.status = "";
            break;

        case WI.WebSocketResource.ReadyState.Connecting:
            var connectionIndicatorElement = document.createElement("div");
            connectionIndicatorElement.classList.add("ready-state", "connecting");
            connectionIndicatorElement.title = WI.UIString("Connecting");

            this.status = connectionIndicatorElement;
            break;

        case WI.WebSocketResource.ReadyState.Open:
            var connectionIndicatorElement = document.createElement("div");
            connectionIndicatorElement.classList.add("ready-state", "open");
            connectionIndicatorElement.title = WI.UIString("Open");

            this.status = connectionIndicatorElement;
            break;
        }
    }
};
