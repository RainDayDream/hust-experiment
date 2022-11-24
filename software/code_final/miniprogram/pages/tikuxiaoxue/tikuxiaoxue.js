// pages/tikuxiaoxue/tikuxiaoxue.js
const app = getApp()
Page({
  goxiaoxueyinianji(){
    app.globalData.globalPhase=0
    wx.navigateTo({
      url: '/pages/tikuxiaoxue1/tikuxiaoxue1',
    })
  },
  goxiaoxueyinianji2(){
    app.globalData.globalPhase=1
    wx.navigateTo({
      url: '/pages/tikuxiaoxue1/tikuxiaoxue1',
    })
  },
  goxiaoxueyinianji3(){
    app.globalData.globalPhase=2
    wx.navigateTo({
      url: '/pages/tikuxiaoxue1/tikuxiaoxue1',
    })
  },
  goxiaoxueyinianji4(){
    app.globalData.globalPhase=3
    wx.navigateTo({
      url: '/pages/tikuxiaoxue1/tikuxiaoxue1',
    })
  },
  goxiaoxueyinianji5(){
    app.globalData.globalPhase=4
    wx.navigateTo({
      url: '/pages/tikuxiaoxue1/tikuxiaoxue1',
    })
  },
  goxiaoxueyinianji6(){
    app.globalData.globalPhase=5
    wx.navigateTo({
      url: '/pages/tikuxiaoxue1/tikuxiaoxue1',
    })
  }
})