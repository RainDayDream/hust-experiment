// pages/tikuxiaoxue1/tikuxiaoxue1.js
const app = getApp()
Page({
  goxiaoxue1math(){
    app.globalData.globalSub=1
    wx.navigateTo({
      url: '/pages/xiaoxue1math/xiaoxue1math',
    })
  },
  goxiaoxue1chinese(){
    app.globalData.globalSub=0
    wx.navigateTo({
      url: '/pages/xiaoxue1math/xiaoxue1math',
    })
  },
  goxiaoxue1english(){
    app.globalData.globalSub=2
    wx.navigateTo({
      url: '/pages/xiaoxue1math/xiaoxue1math',
    })
  }
})