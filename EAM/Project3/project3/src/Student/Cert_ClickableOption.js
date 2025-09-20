import React from 'react';

const ClickableOption = ({ id, label, isSelected, onSelect }) => {
  const handleClick = () => {
    onSelect(id);
  };

  const optionStyle = {
    display: 'flex',
    alignItems: 'center',
    margin: '10px',
    cursor: 'pointer',
  };

  const circleStyle = {
    width: '30px',
    height: '30px',
    borderRadius: '50%',
    backgroundColor: isSelected ? 'blue' : 'lightgray',
    marginRight: '10px',
  };

  return (
    <div style={optionStyle} onClick={handleClick}>
      <div style={circleStyle}></div>
      <span>{label}</span>
    </div>
  );
};

export default ClickableOption;
