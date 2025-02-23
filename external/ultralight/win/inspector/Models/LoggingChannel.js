/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
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

WI.LoggingChannel = class LoggingChannel
{
    constructor(source, level)
    {
        console.assert(typeof source === "string");
        console.assert(source === WI.ConsoleMessage.MessageSource.Media || source === WI.ConsoleMessage.MessageSource.WebRTC || source === WI.ConsoleMessage.MessageSource.MediaSource);

        console.assert(typeof level === "string");
        console.assert(Object.values(WI.LoggingChannel.Level).includes(level));

        this._source = source;
        this._level = level;
    }

    // Payload

    static fromPayload(payload)
    {
        return new WI.LoggingChannel(payload.source, payload.level);
    }

    // Public

    get source() { return this._source; }
    get level() { return this._level; }
};

WI.LoggingChannel.Level = {
    Off: "off",
    Basic: "basic",
    Verbose: "verbose",
};
