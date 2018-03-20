<template>
<v-layout fluid>
  
  <v-flex xs6 pt-2>
  <div class="white elevation-2">
    <v-toolbar flat dense class ="cyan" dark>
       <v-toolbar-side-icon @click="navigateTo({name:'project',params: {projectId: projectId}})">back</v-toolbar-side-icon>
    <v-toolbar-title>View Card</v-toolbar-title>
    </v-toolbar>
    <div>
  <!-- <span v-for="n in team" v-bind:key="n._id" items.push(n._id)</span> -->
</div>
  
  <div class="pl-4 pr-4 pt-2 pb-2">
  <v-text-field label="Title" 
 v-model="title" ></v-text-field>
    <br>
       <v-text-field label="Created By" :disabled="true"
 v-model="creator" ></v-text-field>
    <br>
 
  <v-text-field multi-line label="Description" :rules="[() => description.length > 0 || 'This field is required']"
v-model="description" ></v-text-field>
  <br>

  <v-select
      :items="project._team.map(member => member.username)"
      v-model="owner"
      label="Owner"
    ></v-select>
    <v-menu
        ref="menu"
        lazy
        :close-on-content-click="false"
        v-model="menu"
        transition="scale-transition"
        offset-y
        full-width
        :nudge-right="40"
        max-width="290px"
        min-width="290px"
        :return-value.sync="date"
      >
        <v-text-field
          slot="activator"
          label="Deadline"
          v-model="deadline"
          prepend-icon="event"
        ></v-text-field>
        <v-date-picker
          v-model="deadline"
          no-title
          scrollable
        >
          <v-spacer></v-spacer>
          <v-btn flat color="primary" @click="menu = false">Cancel</v-btn>
          <v-btn flat color="primary" @click="$refs.menu.save(date)">OK</v-btn>
        </v-date-picker>
      </v-menu>

    <!-- <v-date-picker v-model="deadline" :disabled="!isOwner"></v-date-picker> -->
    </div>

  </div>
 
 
  <!--VIF HERE-->
   <v-btn :disabled="!isOwner" @click="save" dark>Save</v-btn>
   <v-btn class="red" :disabled="!isOwner" @click="deleteCard" dark>Delete</v-btn>

  </div>
  </div>
 </v-flex>
   
   <v-flex xs6 pt-2>
 <div class="white elevation-2">
    <v-toolbar flat dense class ="cyan" dark> 
      <v-btn outline color="white" small absolute middle right @click="navigateTo({name:'add-comment',params: {cardId: cardId, projectId: projectId}})">
    <v-icon>add</v-icon>
       </v-btn>
          <v-toolbar-title>Comments</v-toolbar-title>
    </v-toolbar>
    <div   
      v-for="comments in card._comments" 
      :key="comments._creator">
        {{comments.text}} - {{comments._creator.username}} - {{comments.createdAt.trim(date)}}  <v-btn v-if="$store.state.user.username == comments._creator.username" class="red" @click="deleteComment(comments._id)" dark>Delete</v-btn>
      </div>
 </div>
   </v-flex>
</v-layout>
</template>

<script>
import CardService from '@/services/CardsService'
import ProjectService from '@/services/ProjectsService'
import CommentService from '@/services/CommentService'
export default {
  data() {
    return {
      error: null,
      description: null,
      isOwner: false,
      title: null,
      creator: null,
      owner: null,
      card: null,
      team:[],
      deadline:null,
      userId: null,
      project: null,
      projectId:this.$store.state.route.params.projectId,
      cardId:this.$store.state.route.params.cardId
          }
    },
    methods: {
      async deleteComment(commentId){
        console.log(commentId);
      try { 
      await (await CommentService.delete({ //_id, title, description, board, userId, deadline, isDeleted
      _id:commentId,
      isDeleted: true,
      }))
      vm.$forceUpdate();
    } catch (error) {
      this.error = error.response.data;
  }
  },
      async deleteCard(){
      try { 
      await (await CardService.delete({ //_id, title, description, board, userId, deadline, isDeleted
      _id:this.$store.state.route.params.cardId,
      isDeleted: true,
      }))
     this.navigateTo({name:'project',params: {projectId: this.projectId}})
    } catch (error) {
      this.error = error .response.data;
  }
      },
       navigateTo(link, board){
            this.$router.push(link)
        }
          //found this card id parameter within the vuex program, could probably re-send it for clealiness.
        ,
      async save () {
      try { 
      await (await CardService.edit({ //_id, title, description, board, userId, deadline, isDeleted
      _id:this.$store.state.route.params.cardId,
      title: this.title,
      description: this.description,
      deadline: this.deadline,
      owner: this.owner,
      }))
      this.navigateTo({name:'project',params: {projectId: this.projectId}})
    } catch (error) {
      this.error = error .response.data;
  }}},
  async mounted () {
    this.project = (await ProjectService.show({projectId:this.projectId})).data.data[0]

    try {
      this.card = (await CardService.getCardById({cardId:this.cardId})).data.data[0];
      this.creator = this.card._creator.username;
      this.title = this.card.title;
      this.description = this.card.description;
      this.deadline = this.card.deadline;
      this.owner = this.card._owner;
      this.board = this.card.board;
      if (this.card._owner == this.$store.state.user.username) {
        this.isOwner = true;
        console.log(this.isOwner);
        console.log(this.description)
      }
      console.log(this.owner);
   }catch(err){
      console.log(err);
    }
  },
}

</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
.error {
  color:red; 
}


</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
