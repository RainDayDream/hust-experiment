const app = getApp()
let danxuan = [] 
Page({
  data:{
    subject:null,
    current:0,
    total:0,
    cur_question:null,
    //question:[]
  },
  onLoad() {
    danxuan = app.globalData.globalDanxuan
      this.setData({
        total:danxuan.length,
        current:app.globalData.globalCollectionNum,
      })
      this.setData({
        subject:danxuan[this.data.current]
      })
  },

  next(){
    if(this.data.current+1 >= this.data.total){
      wx.showToast({
        icon:"error",
        title: '已经是最后一道题啦'
      })
      return
    }
    else{
      this.setData({
        current : this.data.current + 1,
      })
      
        this.setData({
          subject:danxuan[this.data.current]
        })
     
    }
  },

  pre(){
    if(this.data.current <= 0){
      wx.showToast({
        icon:"error",
        title: '已经是第一道题啦'
      })
      return
    }
    else{
      this.setData({
        current : this.data.current - 1,
      })

        this.setData({
          subject:danxuan[this.data.current ]
        })
    }
  }
})