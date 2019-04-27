const path = require('path');
const VueLoaderPlugin = require("vue-loader/lib/plugin");
const APP_DIR = path.resolve(`src/index.js`);
const BUILD_DIR = path.resolve("dist");
const config = require('../config/config');
const HTMLWebpackPlugin = require('html-webpack-plugin');

module.exports = {
    entry: {
        index: [APP_DIR]
    },
    output: {
        path: BUILD_DIR,
        filename: config.production ? "[name].[hash].build.js" : "[name].build.js",
    },
    module: {
      rules: [
        {
          test: /\.css$/,
          use: [
            'vue-style-loader',
            'css-loader'
          ],
        },      {
          test: /\.vue$/,
          loader: 'vue-loader',
          options: {
            loaders: {
            }
            // other vue-loader options go here
          }
        },
        {
          test: /\.js$/,
          loader: 'babel-loader',
          exclude: /node_modules/
        },
        {
          test: /\.(png|jpg|gif|svg)$/,
          loader: 'file-loader',
          options: {
            name: config.production ? "[name].[ext].[hash]" : "[name].[ext]"
          }
        }
      ]
    },
    resolve: {
      alias: {
        'vue$': 'vue/dist/vue.esm.js'
      },
      extensions: ['*', '.js', '.vue', '.json']
    },
    plugins: [
        new VueLoaderPlugin(),
        new HTMLWebpackPlugin({
            template: path.resolve('public/index.html'),
            inject: true,
            hash: config.production ? true : false
        })
    ]
}