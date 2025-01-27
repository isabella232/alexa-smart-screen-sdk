/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

const HtmlWebpackPlugin = require('html-webpack-plugin');

const path = require('path');
const webpack = require('webpack');

const SRC = path.resolve(__dirname, 'src');
const DEST = path.resolve(__dirname, 'dist');

module.exports = (env) => {
    return {
        mode: 'production',
        context: SRC,
        entry: {
            'main': './main.tsx'
        },

        output: {
            filename: '[name].bundle.js',
            path: DEST,
            publicPath : ''
        },

        resolve: {
            extensions: ['.ts', '.js', '.tsx', '.json', '.css'],
            modules: [
                SRC,
                'node_modules'
            ]
        },

        module: {
            rules: [
                {
                    enforce: 'pre',
                    test: /\.(ts|tsx)?$/,
                    exclude: /node_modules/,
                    use: 'tslint-loader'
                },
                {
                    test: /\.(ts|tsx)?$/,
                    use: 'ts-loader',
                    exclude: /node_modules/
                },

                {
                    test: /\.css$/,
                    use: [
                        { loader: 'style-loader' },
                        {
                            loader: 'css-loader',
                            options: {
                                esModule: false
                            }
                        }
                    ]
                },
                {
                    test: /\.(png|jpg|gif|wav|woff|woff2|eot|ttf|otf)$/,
                    type: 'asset/resource'
                }
            ]
        },

        plugins: [
            new HtmlWebpackPlugin(),
            new webpack.DefinePlugin({
                DISABLE_WEBSOCKET_SSL: JSON.stringify(env.DISABLE_WEBSOCKET_SSL === 'true'),
                USE_UWP_CLIENT: JSON.stringify(env.USE_UWP_CLIENT === 'true'),
                RTCSC_ENABLED: JSON.stringify(env.RTCSC_ENABLED === 'true')
            })
        ]
    };
}
