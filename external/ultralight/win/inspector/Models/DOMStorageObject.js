/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
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

WI.DOMStorageObject = class DOMStorageObject extends WI.Object
{
    constructor(id, host, isLocalStorage)
    {
        super();

        this._id = id;
        this._host = host;
        this._isLocalStorage = isLocalStorage;
        this._entries = new Map;
    }

    // Public

    get id() { return this._id; }
    get host() { return this._host; }
    get entries() { return this._entries; }

    saveIdentityToCookie(cookie)
    {
        cookie[WI.DOMStorageObject.HostCookieKey] = this.host;
        cookie[WI.DOMStorageObject.LocalStorageCookieKey] = this.isLocalStorage();
    }

    isLocalStorage()
    {
        return this._isLocalStorage;
    }

    getEntries(callback)
    {
        function innerCallback(error, entries)
        {
            if (error)
                return;

            for (let [key, value] of entries) {
                if (!key || !value)
                    continue;

                this._entries.set(key, value);
            }

            callback(error, entries);
        }

        DOMStorageAgent.getDOMStorageItems(this._id, innerCallback.bind(this));
    }

    removeItem(key)
    {
        DOMStorageAgent.removeDOMStorageItem(this._id, key);
    }

    setItem(key, value)
    {
        DOMStorageAgent.setDOMStorageItem(this._id, key, value);
    }

    itemsCleared()
    {
        this._entries.clear();
        this.dispatchEventToListeners(WI.DOMStorageObject.Event.ItemsCleared);
    }

    itemRemoved(key)
    {
        this._entries.delete(key);
        this.dispatchEventToListeners(WI.DOMStorageObject.Event.ItemRemoved, {key});
    }

    itemAdded(key, value)
    {
        this._entries.set(key, value);
        this.dispatchEventToListeners(WI.DOMStorageObject.Event.ItemAdded, {key, value});
    }

    itemUpdated(key, oldValue, value)
    {
        this._entries.set(key, value);
        this.dispatchEventToListeners(WI.DOMStorageObject.Event.ItemUpdated, {key, oldValue, value});
    }
};

WI.DOMStorageObject.TypeIdentifier = "dom-storage";
WI.DOMStorageObject.HostCookieKey = "dom-storage-object-host";
WI.DOMStorageObject.LocalStorageCookieKey = "dom-storage-object-local-storage";

WI.DOMStorageObject.Event = {
    ItemsCleared: "dom-storage-object-items-cleared",
    ItemAdded: "dom-storage-object-item-added",
    ItemRemoved: "dom-storage-object-item-removed",
    ItemUpdated: "dom-storage-object-updated",
};
