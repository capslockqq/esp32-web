import PropTypes from 'prop-types';
import { styled } from '@mui/material/styles';

export const Logo = styled((props) => {


  return (
    <><img style={{width:'220px'}} src='/static/images/esp.png'/>
    <h1 style={{padding:'0px', margin:'0px', fontSize:'25px', color:'white', textDecoration:'none !important'}} >ESP32 - Visualizer</h1></>
  );
})``;

Logo.defaultProps = {
  variant: 'primary'
};

Logo.propTypes = {
  variant: PropTypes.oneOf(['light', 'primary'])
};
