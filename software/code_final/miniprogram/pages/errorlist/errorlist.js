const app=getApp()
Page({  
  goChinese(){
    app.globalData.globalSubErr='chinese'
    wx.navigateTo({
    url: '/pages/errorclt/errorclt',
    })

  },
  goEnglish(){
    app.globalData.globalSubErr='english'
    wx.navigateTo({
    url: '/pages/errorclt/errorclt',
    })
  },
  goMaths(){
    app.globalData.globalSubErr='math'
    wx.navigateTo({
    url: '/pages/errorclt/errorclt',
    })
  }
})