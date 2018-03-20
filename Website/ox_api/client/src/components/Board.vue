<template>
<v-layout container>
  <div class="white elevation-2">
    <v-toolbar flat dense class ="grey" light>
      <!--parameters is the only way to go when we're passing project ID to navigate methods! Props are strictly for
      the components!-->
      <v-btn v-if="button=='true'" outline color="white"  class="dragArea" small absolute middle right @click="navigateTo({name:'add-card',params: 
          {projectId: projId, board:title}})">
        <slot name ="action"/>
    <v-icon>add</v-icon>
       </v-btn>
             <v-toolbar-title>{{title}}</v-toolbar-title>
    </v-toolbar>

 
  <div class="pl-2 pr-2 pt-2 pb-2">
      <draggable @update="onUpdate()" v-model="board"  class="dragArea" :list=board :options="{group:'board'}"  @start="drag=true" 
                @end="drag=false" :drop="onDrop" :move="onMove">
     <!-- <div v-for="cards in board"
      :key="cards._id"> -->    
        <v-list-tile v-for="cards in board" :key="cards._id" @click="navigateTo({name:'card',
          params: {cardId: cards._id, projectId:projectId}})" color="black" >         
            <v-list-tile-content>
              <v-list-tile-title>{{ cards.title }}</v-list-tile-title>
              <v-list-tile-sub-title>{{ cards._owner }}</v-list-tile-sub-title>
            </v-list-tile-content>
            <v-list-tile-action>
              <v-btn icon ripple>
                <v-icon color="grey lighten-1">info</v-icon>
              </v-btn>
            </v-list-tile-action>
          </v-list-tile>
        </draggable>


   </div>

        <!-- <div v-if="(empty)" class="pl-4 pr-4 pt-2 pb-2">
      <draggable @update="onUpdate()" v-model="board"  :list=board :options="{group:'board'}"  @start="drag=true" 
                @end="drag=false" :drop="onDrop" :move="onMove">
     <ul>
       {{tempCard}}
          </ul>
          </draggable>

          </div> -->
  
   </div>
  </div>
    
  </div>

</v-layout>
</template>

<script>
import CardsService from '@/services/CardsService'
import ProjectService from '@/services/ProjectsService'
import draggable from 'vuedraggable';


export default {

   components: {
    draggable
  },
//TODO: DELETE BLANKS.
  data() {
    return {
      ghost: null,
      link: '',
      error: null,
      board: null,
      res: null,
      var: null,
      staged: null,
      song: null,
      tempCard: null,
      update: null,
      projectId: this.$store.state.route.params.projectId,
      dragging: false,
    futureIndex:null,
    future_index: "START",
      }
    
  },
  methods: {
      onMove: function(event, oEvent) {
      var originBoard = (event.draggedContext.element);
      var destinationBoard = (event.relatedContext.element);
      
  
      console.log(originBoard.board);
      console.log(originBoard._id);
      console.log(destinationBoard.board);

    if (originBoard.board != destinationBoard.board) {
      try{
        CardsService.updateBoard({_id:originBoard._id, board:destinationBoard.board});
        }catch(err) {
          console.log(err)
        }
       
       
    }
     }, //TODO: write the update code here
    onDrop: function(event, oEvent) {
      console.log("French");
    },
     getComponentData() {
      return {
        on: {
          change: this.handleChange,
          input: this.inputChanged
        },
        props: {
          value: this.activeNames
        }
      }},
        navigateTo(link, board){
            this.$router.push(link)
        }
         },
  props: [
    'title',
    'projId',
    'button',
    'empty'
      ],
       created() {
    document.addEventListener('beforeunload', this.handler)
  },
      async mounted () {
    const projectId = this.$store.state.route.params.projectId;

    this.board = (await CardsService.getCardsByProject({projectId:projectId,board:this.title})).data.data;
      
}}
    //everytime we change routes on the dev tools, the route changed is being dispatched.
    //viex-router-sync is a way to map the dispatch events when the route changes
  //  const project = await ProjectService.show({projectId:projectId})
    
  


</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
.dragArea {
  min-height: 10px;
}
</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
