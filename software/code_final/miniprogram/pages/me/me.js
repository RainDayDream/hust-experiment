const app = getApp()
const db=wx.cloud.database()

Page({
    data:
    {
        userInfo:'',
        picker:['小学一年级','小学二年级','小学三年级','小学四年级','小学五年级','小学六年级','初中一年级','初中二年级','初中三年级','高中一年级','高中二年级','高中三年级'],
        index:null,
        grade:'',
        userOpenId:'',
        s:0
    },
    //授权登錄
  login()
  {
    wx.cloud.callFunction({
      name:"getopenid",
      complete:res=>{
        this.setData({
          userOpenId:res.result.openid
        })
        app.globalData.globalUserid = this.data.userOpenId
        console.log('用户id', app.globalData.globalUserid)
       console.log('获取openid成功',res)
    }
  })
      wx.getUserProfile({
          desc:'用于完善会员信息',
          success:(res)=>{
              let user=res.userInfo
            console.log('授权成功',res)
            this.setData({
                userInfo:user
            })
            db.collection('userinfo').add({
              data:{
                _id:this.data.userOpenId,
                nickName:this.data.userInfo.nickName,
                images:this.data.userInfo.avatarUrl
              },
              success(res){
                console.log('添加数据成功',res)
              },
              fail(res){
                console.log('添加失败',res)
              }
              })
              db.collection('math').add({
                data:{
                  _id:this.data.userOpenId,
                  nums:0,
                  errs:[]
                },
                success(res){
                  console.log('添加數學錯題集数据成功',res)
                },
                fail(res){
                  console.log('添加數學錯題集失败',res)
                }
                })
              db.collection('chinese').add({
                data:{
                  _id:this.data.userOpenId,
                  nums:0,
                  errs:[]
                },
                success(res){
                  console.log('添加中文錯題集数据成功',res)
                },
                fail(res){
                  console.log('添加中文錯題集失败',res)
                }
                })
                db.collection('english').add({
                  data:{
                    _id:this.data.userOpenId,
                    nums:0,
                    errs:[]
                  },
                  success(res){
                    console.log('添加英文錯題集数据成功',res)
                  },
                  fail(res){
                    console.log('添加英文錯題集失败',res)
                  }
                  })
                  db.collection('my_questionList').add({
                    data:{
                      _id:this.data.userOpenId,
                      phase:0,
                      subject:0
                    },
                    success(res){
                      console.log('添加我的題庫成功',res)
                    },
                    fail(res){
                      console.log('添加我的題庫失败',res)
                    }
                    })
                    db.collection('myCollection').add({
                      data:{
                        _id:this.data.userOpenId,
                        collectionList:[],
                        questionList:[],
                        titles:[]
                      },
                      success(res){
                        console.log('添加我的題庫成功',res)
                      },
                      fail(res){
                        console.log('添加我的題庫失败',res)
                      }
                      })
          },
          fail(res)
          {
              console.log('授权失敗',res)
          }
      })
      
  },
  //退出登錄
  logOut()
  {
    this.setData({
        userInfo:'',
        grade:''
    })
  },

  // mistakes()
  // {
  //   wx.switchTab({
  //     url: '/pages/errorclt/errorclt',
  //   })
  // },

  // collections()
  // {
  //   wx.navigateTo({
  //       url:"/pages/collections/collections"
  //   })
  // },

    PickerChange(e){

      console.log(e)
      this.setData({
        index:e.detail.value
      })
      app.globalData.globalUserGrade=e.detail.value
      if(this.data.index==0){
        this.setData({
          grade:'小学一年级'
        })
      }
      else  if(this.data.index==1){
        this.setData({
          grade:'小学二年级'
        })
      }
      else  if(this.data.index==2){
        this.setData({
          grade:'小学三年级'
        })
      }
      else  if(this.data.index==3){
        this.setData({
          grade:'小学四年级'
        })
      }
      else  if(this.data.index==4){
        this.setData({
          grade:'小学五年级'
        })
      }
      else  if(this.data.index==5){
        this.setData({
          grade:'小学六年级'
        })
      }
      else  if(this.data.index==6){
        this.setData({
          grade:'初中一年级'
        })
      }
      else  if(this.data.index==7){
        this.setData({
          grade:'初中二年级'
        })
      }
      else  if(this.data.index==8){
        this.setData({
          grade:'初中三年级'
        })
      }
      else  if(this.data.index==9){
        this.setData({
          grade:'高中一年级'
        })
      }
      else  if(this.data.index==10){
        this.setData({
          grade:'高中二年级'
        })
      }
      else{
        this.setData({
          grade:'高中三年级'
        })
      }
      db.collection('userinfo').doc(this.data.userOpenId).update({
        data:{
          grade:this.data.grade
        },
        success(res){
          console.log('添加数据成功',res)
        },
        fail(res){
          console.log('添加失败',res)
        }
        })
    },
  report(){
    wx.navigateTo({
      url: '/pages/record/record',
    })
  },
  collections(){
    wx.navigateTo({
      url: '/pages/collection/collection',
    })
  },
  errorlist(){

    wx.switchTab({
      url: '/pages/errorlist/errorlist',
    })
  },
})
