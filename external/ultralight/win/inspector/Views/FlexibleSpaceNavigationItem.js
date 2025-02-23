/*
 * Copyright (C) 2013-2017 Apple Inc. All rights reserved.
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

WI.FlexibleSpaceNavigationItem = class FlexibleSpaceNavigationItem extends WI.NavigationItem
{
    constructor(navigationItem, alignItem)
    {
        super();

        console.assert(!navigationItem || navigationItem instanceof WI.NavigationItem);

        this._navigationItem = navigationItem || null;

        if (this._navigationItem) {
            this._navigationItem = navigationItem;
            this.element.classList.add(alignItem || WI.FlexibleSpaceNavigationItem.Align.Start);
        }
    }

    // Protected

    get additionalClassNames()
    {
        return ["flexible-space"];
    }

    updateLayout(expandOnly)
    {
        super.updateLayout(expandOnly);

        if (!this._navigationItem)
            return;

        if (expandOnly) {
            let flexibleWidth = this.width;
            if (!flexibleWidth)
                return;

            this.element.appendChild(this._navigationItem.element);

            this._navigationItem.updateLayout(true);
            let itemWidth = this._navigationItem.width;

            let remainingWidth = flexibleWidth - itemWidth;
            if (remainingWidth <= 0)
                this.element.removeChild(this._navigationItem.element);
        }
    }
};

WI.FlexibleSpaceNavigationItem.Align = {
    Start: "align-start",
    End: "align-end",
};
