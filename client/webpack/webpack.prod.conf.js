const path = require("path"),
  webpack = require("webpack"),
  merge = require("webpack-merge"),
  base = require("./webpack.base.conf.js");

module.exports = merge(base, {
  mode: "production",
  optimization: {
    minimize: true,
    runtimeChunk: "single",
    splitChunks: {
      cacheGroups: {
        vendor: {
          test: /[\\/]node_modules[\\/]/,
          name: "vendors",
          chunks: "all"
        }
      }
    }
  },
  plugins: [
    new webpack.DefinePlugin({
      "process.env": {
        NODE_ENV: '"production"'
      }
    }),
    new webpack.LoaderOptionsPlugin({
      minimize: true
    }),
    new webpack.HashedModuleIdsPlugin()
  ],
  performance: {
    hints: false
  },
  devtool: "source-map"
});