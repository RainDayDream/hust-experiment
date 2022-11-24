// pages/home/home.js
Page({
  data:{
    imageList:[
      "https://gd-hbimg.huaban.com/2b5b3c52a50c066edc2f56f5483f7a50a218eb63a879-Y85GuZ_fw658",
      "https://gd-hbimg.huaban.com/6872b456c6373dd90b45e52e88ee9b215b5cbab771010-7bTRMt_fw658",
      "https://gd-hbimg.huaban.com/c977588f3894b52d6e49972be53aea2195533a437f1c-lDzTWJ_fw658",
      "https://gd-hbimg.huaban.com/8e13a678553e3bfe03b2106d38238564c9733b0bc0e5a-etatQx_fw658"
    ]
  },

  gotiku(){
    wx.navigateTo({
      url: '/pages/tikuxiaoxue/tikuxiaoxue',
    })
  },

  gomytiku(){
    wx.navigateTo({
      url: '/pages/mytiku/mytiku',
    })
  },
  goToCollection(){
    wx.navigateTo({
      url: '/pages/collection/collection',
    })
  }
})