const path = require("path"),
  webpack = require("webpack"),
  merge = require("webpack-merge"),
  base = require("./webpack.base.conf.js");

module.exports = merge(base, {
  mode: "development",
  output: {
    publicPath: "/",
  },
  devServer: {
    contentBase: path.resolve("dist"),
    compress: true,
    open: true,
    hot: true,
    noInfo: true,
    overlay: true,
    historyApiFallback: true
  },
  performance: {
    hints: false
  },
  devtool: "eval-source-map"
});