// pages/currentErr/currentErr.js
const app = getApp()
let danxuan = [] 

Page({
  data: {
    total:0,
    question:[],
  },
  onLoad: function (options) {
    danxuan = []
  for (var i=0;i<app.globalData.globalDanxuan.length;i++){ 
    danxuan[i] = app.globalData.globalDanxuan[i]
    console.log('danxuan[i]',danxuan[i])
    }    
    console.log('danxuan',danxuan)
  this.setData({
    question:danxuan,
    total :danxuan.length
  })
  },
  seeQuestion(e){
     console.log('e.currentTarget.dataset.index',e.currentTarget.dataset.index); //我是固定参数
    app.globalData.globalCollectionNum=e.currentTarget.dataset.index
    wx.navigateTo({
      url: '/pages/currentErrdetail/currentErrdetail',
    })
  }
})