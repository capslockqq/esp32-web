import { Button, TextField } from '@mui/material';
import { Box, keys } from '@mui/system';
import { DashboardLayout } from '../components/dashboard-layout';
import axios from "axios"
import { useEffect, useState } from 'react';


function Parameters() {
  const [parameters, setParameter] = useState([]);
  const [newParameters, setNewParameters] = useState([]);
  const [loading, setLoading] = useState(false);
  const get_all_parameters = () => {
    axios.get('http://192.168.0.87/AllParameters').then(res => {
      setParameter(res.data["parameters"]);
    }).catch(err => {
      console.log(err);
    })
  }
  useEffect(() => {
    get_all_parameters();
  }, [])

  const some_method = (event) => {
    let new_list = newParameters
    let item = { id: event.target.id, new_value: parseInt(event.target.value) || event.target.value }
    console.log(item.new_value)
    let index = new_list.findIndex(x => (x.id == item.id))
    if (index >= 0) {
      if (!item.new_value || item.new_value === "") {
        new_list.splice(index, 1);
      }
      else {
        new_list.at(index).new_value = item.new_value
      }
    }
    else {
      new_list.push(item)
    }
    setNewParameters(new_list)
    console.log("new parameters", newParameters)
  }

  const changeParameters = () => {
    setLoading(true);
    axios.post('http://192.168.0.87/SetParameters', JSON.stringify({ parameters: newParameters })).then(res => {
      get_all_parameters();
      setLoading(false);
    })
      .catch(err => {
        console.log(err)
      })
  }

  let allParameters = Object.keys(parameters).length ? parameters.map(element => {
    return <Box
      sx={{
        flexGrow: 1,
        marginTop: 2
      }}>
      <h3 style={{ lineHeight: '5px' }}>{element['name']}</h3>
      <TextField
        label={`${element['value']} ${element['unit']}`}
        margin="normal"
        id={element['id']}
        onChange={(e) => some_method(e)}
        variant="outlined"
      />
    </Box>
  }) : "";
  return (
    <Box
      component="main"
      sx={{
        flexGrow: 1,
        marginLeft: 10
      }}
    >
      <h1>All parameters</h1>
      {allParameters}
      <Button
        disabled={loading}
        onClick={changeParameters}
        color="primary"
        variant="contained"
        sx={{
          width: "268px",
          fontSize:20
        }}>
        Update paramters
      </Button>
    </Box>)
}

Parameters.getLayout = (page) => (
  <DashboardLayout>
    {page}
  </DashboardLayout>
);

export default Parameters;