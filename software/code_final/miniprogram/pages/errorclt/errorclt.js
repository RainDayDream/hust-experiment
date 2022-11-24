const app = getApp()
let title = []
Page({
  data:{
    subject:null,
    current:1,
    total:0,
    kemu:null,
    questionid:'',
    cur:1,
  },
  onLoad() {
    this.setData({
      kemu:app.globalData.globalSubErr
    })
    const db = wx.cloud.database()
    const _ = db.command
    db.collection(this.data.kemu).doc(app.globalData.globalUserid)
    .get().then(res=>{
      console.log('res',res)
      title = res.data.errs
      this.setData({
        total:res.data.errs.length,
        subject:res.data.errs[0],
        questionid:res.data.errs[0]._id
      })
      console.log("err",title)
      console.log("total",this.data.total)
    })
  },

  next(){
    let current = this.data.current + 1
    if(current > title.length){
      wx.showToast({
        icon:"error",
        title: '已经是最后一道题啦'
      })
      return
    }
    this.setData({
      current:current,
      subject:title[current-1],
      cur:current
    })
  },

  pre(){
    let current = this.data.current - 1
    if(current <= 0){
      wx.showToast({
        icon:"error",
        title: '已经是第一道题啦'
      })
      return
    }
    this.setData({
      current:current,
      subject:title[current-1],
      cur:current
    })
  },
  errNULL()
  {
    wx.navigateTo({
      url: '/pages/mytiku/mytiku',
    })
  },
  async delete()
  {

    let cur_id = this.data.questionid
    console.log('current_id', this.data.questionid)
    console.log('删除错题集')
    this.setData({
      total:this.data.total-1
    })
    const db = wx.cloud.database()
    const _ = db.command
    await db.collection(this.data.kemu).doc(app.globalData.globalUserid).update({
      data: {
        errs: _.pull({
          _id: _.eq(cur_id),
        }),
        nums:this.data.total
      },
      
    })
    title=[]
    await db.collection(this.data.kemu).doc(app.globalData.globalUserid)
    .get().then(res=>{
      console.log('res',res)
      title = res.data.errs
      this.setData({
        total:res.data.errs.length,
        subject:res.data.errs[0],
        questionid:res.data.errs[0]._id
      })
      console.log("total",title)
    })

  },

})