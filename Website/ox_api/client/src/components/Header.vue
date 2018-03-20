<template>
<v-toolbar fixed class="cyan" dark>
    <v-toolbar-title class="mr4"><span class="home" @click="navigateTo({name:'home'})">X&ZUMO.</span></v-toolbar-title>
<v-toolbar-items>
     <v-btn v-if="$store.state.isUserLoggedIn" flat dark @click="navigateTo({name: 'dashboard'})">
       Dashboard
        </v-btn>
        <v-btn v-if="$store.state.isUserLoggedIn" flat dark @click="deleteAccount()">
       Delete Account
        </v-btn>  
</v-toolbar-items>
<v-spacer></v-spacer>

</v-toolbar-items>
 <!--<router-link to="register">-->
 <v-btn v-if="!$store.state.isUserLoggedIn" flat dark @click="navigateTo({name:'register'})">
       Sign Up
        </v-btn>

<v-btn v-if="!$store.state.isUserLoggedIn" flat dark @click="navigateTo({name:'login'})">
       Login
        </v-btn>
 <v-btn v-if="$store.state.isUserLoggedIn" flat dark @click="logout">
       Log Out
        </v-btn>       
<!--</router-link>-->
</v-toolbar>
</v-toolbar>

</template>
<script>
import AuthenticationService from '@/services/AuthenticationService'

export default {
    
    methods: {
        navigateTo(link){
            this.$router.push(link)
        },
        async deleteAccount(){
        var r = confirm("Are you sure you want to delete your account?");
        if (r == true) 
        {
        //delete account
          try {
              (await AuthenticationService.delete({_id:this.$store.state.user._id,isDeleted:true}))
          }catch (err){
              console.log(err);
          }
        }
            this.$store.dispatch('setToken', null)
            this.$store.dispatch('setUser', null)
            this.$router.push({name: 'home'})
        },
        logout () {
            this.$store.dispatch('setToken', null)
            this.$store.dispatch('setUser', null)
            this.$router.push({name: 'home'})
        }
    }
}
</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
.home {
    cursor: pointer;
}
.home:hover {
    color:aquamarine;
}
.error {
  color:red; 
}


</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
