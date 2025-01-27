/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

import * as React from 'react';
import { IAPLRendererWindowConfig } from '../lib/config/IDeviceAppConfig';
import {FocusManager} from '../lib/focus/FocusManager';
import {ActivityTracker} from '../lib/activity/ActivityTracker';
import {
    IRenderPlayerInfoMessage,
    IRenderStaticDocumentMessage,
    IAPLCoreMessage
} from '../lib/messages/messages';
import {
    APLRendererWindow,
    WebsocketConnectionWrapper,
    APLRendererWindowState
} from './APLRendererWindow';
import {
    resolveRenderPlayerInfo
} from '../lib/displayCards/AVSDisplayCardHelpers';
import {DisplayState} from 'apl-client';

interface IPlayerInfoWindowProps {
    playerInfoMessage : IRenderPlayerInfoMessage;
    targetWindowId : string;
    refreshRenderer : boolean;
    windowConfig : IAPLRendererWindowConfig;
    client : WebsocketConnectionWrapper;
    focusManager : FocusManager;
    activityTracker : ActivityTracker;
    aplCoreMessageHandlerCallback :
        (windowId : string, aplCoreMessageHandler : (message : IAPLCoreMessage) => void) => void;
}

interface IPlayerInfoWindowState {
    windowState : APLRendererWindowState;
    targetWindowId : string;
    displayState : DisplayState;
}

export class PlayerInfoWindow extends React.Component<IPlayerInfoWindowProps, IPlayerInfoWindowState> {

    protected client : WebsocketConnectionWrapper;
    protected windowConfig : IAPLRendererWindowConfig;
    protected focusManager : FocusManager;
    protected activityTracker : ActivityTracker;
    protected isRendering : boolean;

    constructor(props : IPlayerInfoWindowProps) {
        super(props);
        this.client = this.props.client;
        this.windowConfig = this.props.windowConfig;
        this.focusManager = this.props.focusManager;
        this.activityTracker = this.props.activityTracker;

        this.state = {
            windowState : APLRendererWindowState.INACTIVE,
            targetWindowId : this.props.windowConfig.id,
            displayState : DisplayState.kDisplayStateHidden
        };
    }

    private getToggleControls(controls : any) : Map<any, any> {
        if (!controls) {
            return new Map();
        }

        return controls.filter((c : any) => c.type === 'TOGGLE').reduce((m : Map<any, any>, c : any) => {
            m.set(c.name, c);
            return m;
        }, new Map() );
    }

    private toggleControlsChanged(controls : any) : boolean {
        const newToggleControls = this.getToggleControls(controls);
        const oldToggleControls = this.getToggleControls(this.props.playerInfoMessage.payload.controls);
        if (newToggleControls.size !== oldToggleControls.size) {
            // Number of controls has changed
            return true;
        }

        for (const [name, control] of newToggleControls) {
            if (!oldToggleControls.has(name)) {
                return true;
            }

            const oldControl = oldToggleControls.get(name);
            if (control.selected !== oldControl.selected ||
                control.enabled !== oldControl.enabled) {
                return true;
            }
        }
        return false;
    }

    protected handleRenderPlayerInfoMessage(renderPlayerInfoMessage : IRenderPlayerInfoMessage) {
        // If not rendering AND
        // we have a new playerInfo message or audioItemId,
        // or toggle controls changed - send a new playerInfo renderDocument request
        if (!this.isRendering && (
            !this.props.playerInfoMessage ||
            (renderPlayerInfoMessage.payload.audioItemId !==
                this.props.playerInfoMessage.payload.audioItemId) ||
            this.toggleControlsChanged(renderPlayerInfoMessage.payload.controls))) {
            const renderStaticDocumentMessage : IRenderStaticDocumentMessage =
                resolveRenderPlayerInfo(renderPlayerInfoMessage, this.props.windowConfig.id);
            this.isRendering = true;
            this.client.sendMessage(renderStaticDocumentMessage);

            this.setState({
                windowState : APLRendererWindowState.ACTIVE
            });
        }
    }

    protected onRendererInit() {
        this.isRendering = false;
    }

    protected onRendererDestroyed() {
        this.isRendering = false;
    }

    public render() {
        // Create Player Info APL Window
        const playerInfo = <APLRendererWindow
            id={this.windowConfig.id}
            key={this.windowConfig.id}
            windowConfig={this.windowConfig}
            clearRenderer={APLRendererWindowState.INACTIVE === this.state.windowState}
            refreshRenderer={this.props.refreshRenderer}
            displayState={this.state.displayState}
            client={this.client}
            focusManager={this.focusManager}
            activityTracker={this.activityTracker}
            onRendererInit={this.onRendererInit.bind(this)}
            onRendererDestroyed={this.onRendererDestroyed.bind(this)}
            aplCoreMessageHandlerCallback={this.props.aplCoreMessageHandlerCallback}
          />;

        return(playerInfo);
    }

    public componentWillReceiveProps(nextProps : IPlayerInfoWindowProps) {
        if (this.props.playerInfoMessage !== nextProps.playerInfoMessage) {
            if (nextProps.playerInfoMessage !== undefined) {
                this.handleRenderPlayerInfoMessage(nextProps.playerInfoMessage);
            } else {
                this.setState({
                    windowState : APLRendererWindowState.INACTIVE,
                    displayState : DisplayState.kDisplayStateHidden
                });
            }
        } else if (nextProps.targetWindowId === undefined &&
            // If the target window is cleared, but the PlayerInfo window
            // is still ACTIVE and STOPPED, we need to re-render
            // to prevent a stale card from showing.
            this.state.windowState === APLRendererWindowState.ACTIVE
            && this.props.playerInfoMessage !== undefined
            && this.props.playerInfoMessage.audioPlayerState === 'STOPPED') {
            this.handleRenderPlayerInfoMessage(this.props.playerInfoMessage);
        } else if (this.state.windowState === APLRendererWindowState.ACTIVE) {
            this.setState({
                displayState: nextProps.targetWindowId === this.windowConfig.id
                    || nextProps.targetWindowId === undefined ?
                    DisplayState.kDisplayStateForeground : DisplayState.kDisplayStateBackground
            });
        }
    }
}
